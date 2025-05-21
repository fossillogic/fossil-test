import argparse
import requests
import os
from datetime import datetime

GITHUB_API = "https://api.github.com"

def fetch_milestone_issues(owner, repo, milestone_title, token=None):
    headers = {"Authorization": f"token {token}"} if token else {}
    
    # Find milestone ID
    milestone_url = f"{GITHUB_API}/repos/{owner}/{repo}/milestones"
    milestone_resp = requests.get(milestone_url, headers=headers).json()
    milestone_id = next((m['number'] for m in milestone_resp if m['title'] == milestone_title), None)
    if milestone_id is None:
        raise ValueError(f"Milestone '{milestone_title}' not found.")

    # Fetch issues
    issues_url = f"{GITHUB_API}/repos/{owner}/{repo}/issues"
    issues = []
    page = 1
    while True:
        params = {
            "milestone": milestone_id,
            "state": "closed",
            "per_page": 100,
            "page": page
        }
        page_issues = requests.get(issues_url, headers=headers, params=params).json()
        if not page_issues:
            break
        issues.extend(page_issues)
        page += 1

    return issues

def group_issues_by_label(issues):
    grouped = {"feature": [], "bug": [], "enhancement": [], "other": []}
    for issue in issues:
        labels = [label["name"] for label in issue["labels"]]
        added = False
        for key in grouped:
            if key in labels:
                grouped[key].append(issue)
                added = True
                break
        if not added:
            grouped["other"].append(issue)
    return grouped

def fetch_repo_description(owner, repo, token=None):
    headers = {"Authorization": f"token {token}"} if token else {}
    url = f"{GITHUB_API}/repos/{owner}/{repo}"
    resp = requests.get(url, headers=headers).json()
    return resp.get("description", "")

def generate_markdown(milestone, grouped_issues, repo_description=""):
    today = datetime.today().strftime("%Y-%m-%d")
    output = [f"# 📦 Release Notes for `{milestone}`", f"_Date: {today}_"]

    if repo_description:
        output.append(f"\n> {repo_description}\n")

    output.append(f"\n## [{milestone}] – {today}")

    if grouped_issues["feature"]:
        output.append("\n### 🚀 Features")
        for issue in grouped_issues["feature"]:
            output.append(f"- {issue['title']} (#{issue['number']})")

    if grouped_issues["bug"]:
        output.append("\n### 🐞 Bug Fixes")
        for issue in grouped_issues["bug"]:
            output.append(f"- {issue['title']} (#{issue['number']})")

    if grouped_issues["enhancement"]:
        output.append("\n### 🛠 Enhancements")
        for issue in grouped_issues["enhancement"]:
            output.append(f"- {issue['title']} (#{issue['number']})")

    if grouped_issues["other"]:
        output.append("\n### 📦 Other")
        for issue in grouped_issues["other"]:
            output.append(f"- {issue['title']} (#{issue['number']})")

    # 🧩 WrapDB Git Definition
    output.append("\n### 🧩 WrapDB Git Definition")
    output.append("```ini")
    output.append("# ======================")
    output.append("# Git Wrap package definition")
    output.append("# ======================")
    output.append("[wrap-git]")
    output.append("url = https://github.com/fossillogic/fossil-test.git")
    output.append(f"revision = v{milestone}")
    output.append("")
    output.append("[provide]")
    output.append("fossil-test = fossil_test_dep")
    output.append("```")

    return "\n".join(output)

def save_to_file(content, filename):
    with open(filename, "a") as f:
        f.write("\n\n" + content.strip() + "\n")

def main():
    parser = argparse.ArgumentParser(description="Pizza Changelog and Release Note Generator")
    parser.add_argument("--owner", required=True, help="GitHub repository owner")
    parser.add_argument("--repo", required=True, help="GitHub repository name")
    parser.add_argument("--milestone", required=True, help="Milestone title")
    parser.add_argument("--token", help="GitHub personal access token (optional)")
    parser.add_argument("--out", default="CHANGELOG.md", help="Output changelog file")
    parser.add_argument("--release-file", action="store_true", help="Also save to release_notes_<milestone>.md")
    args = parser.parse_args()

    issues = fetch_milestone_issues(args.owner, args.repo, args.milestone, args.token)
    grouped = group_issues_by_label(issues)
    markdown = generate_markdown(args.milestone, grouped, fetch_repo_description(args.owner, args.repo, args.token))

    save_to_file(markdown, args.out)
    print(f"✅ Changelog updated: {args.out}")

    if args.release_file:
        rel_file = f"release_notes_{args.milestone.replace('.', '_')}.md"
        save_to_file(markdown, rel_file)
        print(f"📝 Release note saved: {rel_file}")

if __name__ == "__main__":
    main()
