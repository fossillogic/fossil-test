#!/usr/bin/env python3
import subprocess
import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: bedrock_wrapper.py <program> [args...]")
        sys.exit(1)

    cmd = sys.argv[1:]
    sys.exit(subprocess.call(cmd))

if __name__ == '__main__':
    main()
