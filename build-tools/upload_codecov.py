#!/usr/bin/env python

import argparse
import os


def main():
    parser = argparse.ArgumentParser(description="Upload coverage report to codecov.io.")
    parser.add_argument('-b', '--build_path', action='store', required=True, help='Build path')
    parser.add_argument('-t', '--target', action='store', required=True, help="Target to generate coverage files.")
    args = parser.parse_args()

    os.chdir(args.build_path)
    os.system("cmake --build " + args.build_path + " -- " + args.target)
    os.system("lcov --directory . --capture --output-file coverage.info")
    os.system("lcov --remove coverage.info '/usr/*' --output-file coverage.info")
    os.system("lcov --list coverage.info")
    os.system('/bin/bash -c "bash <(curl -s https://codecov.io/bash) || echo \"Codecov did not collect coverage reports\""')

if __name__ == "__main__":
    main()