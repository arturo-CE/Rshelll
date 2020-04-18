#!/bin/sh

../rshell "cat < names.txt"

../rshell "cat < CMakeLists.txt"

../rshell "cat < README.md"

../rshell "wc < names.txt"

../rshell "wc < CMakeList.txt"

../rshell "wc < README.md"

../rshell "exit"

