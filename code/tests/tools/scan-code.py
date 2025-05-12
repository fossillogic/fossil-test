import os
import re
import argparse

# ANSI color codes
CYAN = '\033[96m'
BLUE = '\033[94m'
YELLOW = '\033[93m'
RED = '\033[91m'
RESET = '\033[0m'

def check_format_issues(filepath):
    issues = []
    
    # Pattern: enforce * next to variable name, e.g., "int* ptr", not "int * ptr"
    pointer_pattern = re.compile(
        r'\b(?:const\s+|volatile\s+|restrict\s+)?'
        r'(?:unsigned\s+|signed\s+)?'
        r'(?:int|char|float|double|void|size_t|ptrdiff_t|uint\d+_t|int\d+_t)\s+\*\s+\w+'
    )

    with open(filepath, 'r', encoding='utf-8', errors='ignore') as file:
        for lineno, line in enumerate(file, start=1):
            if '\t' in line:
                issues.append((lineno, 'Tab character found', 'warning'))
            if 'goto' in line:
                issues.append((lineno, 'Usage of "goto" is not allowed', 'error'))
            if pointer_pattern.search(line):
                issues.append((lineno, 'Pointer symbol (*) should be adjacent to variable name (e.g., `int* ptr`)', 'error'))
            if line.strip().startswith('//') and len(line.strip()) > 80:
                issues.append((lineno, 'Comment exceeds 80 characters', 'warning'))
            if line.strip().endswith(';') and line.strip() == ';':
                issues.append((lineno, 'Empty statement found', 'warning'))
    return issues

def scan_directory_for_issues(directory):
    issue_report = {}
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(('.c', '.cpp', '.h', '.hpp')):
                full_path = os.path.join(root, file)
                issues = check_format_issues(full_path)
                if issues:
                    issue_report[full_path] = issues
    return issue_report

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Check C/C++ files for formatting issues.")
    parser.add_argument('directory', help="Directory to scan for source files.")
    args = parser.parse_args()

    report = scan_directory_for_issues(args.directory)
    for filepath, issues in report.items():
        print(f"\n{BLUE}{filepath}:{RESET}")
        for lineno, message, severity in issues:
            color = RED if severity == 'error' else YELLOW
            print(f"  {CYAN}Line {lineno}:{RESET} {color}{message}{RESET}")
