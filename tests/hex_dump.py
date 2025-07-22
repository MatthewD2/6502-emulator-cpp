#!/usr/bin/env python3
import sys
import os

def usage():
    print(f"Usage: {os.path.basename(sys.argv[0])} <binary_file>")
    sys.exit(1)

def main():
    if len(sys.argv) != 2:
        usage()

    filename = sys.argv[1]
    try:
        with open(filename, "rb") as f:
            data = f.read()
    except IOError as e:
        print(f"Error opening file: {e}", file=sys.stderr)
        sys.exit(1)

    hex_bytes = " ".join(f"{b:02X}" for b in data)
    print(hex_bytes)

if __name__ == "__main__":
    main()