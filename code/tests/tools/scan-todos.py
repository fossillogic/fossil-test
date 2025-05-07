import os
import re
import argparse

# ANSI escape codes for colors
BLUE = '\033[94m'
CYAN = '\033[96m'
RESET = '\033[0m'

def find_keywords_in_file(filepath):
    keyword_pattern = re.compile(r'//\s*(TODO|FIX|NODE)[:\s]*(.*)', re.IGNORECASE)
    items = set()
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as file:
        for line in file:
            match = keyword_pattern.search(line)
            if match:
                keyword = match.group(1).upper()
                text = match.group(2).strip()
                if text:
                    items.add(f"{keyword}: {text}")
    return items

def find_keywords_in_directory(directory):
    all_items = set()
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(('.c', '.cpp', '.h', '.hpp')):
                full_path = os.path.join(root, file)
                all_items.update(find_keywords_in_file(full_path))
    return all_items

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Extract unique TODOs, FIXes, and NODEs from C/C++ files.")
    parser.add_argument('directory', help="Directory to scan for source files.")
    args = parser.parse_args()

    items = find_keywords_in_directory(args.directory)
    print(f"{BLUE}Extracted Items:{RESET}")
    for item in sorted(items):
        print(f"{CYAN}- [ ] {item}{RESET}")
