#!/bin/sh

../rshell "strings README.md | grep the"

../rshell "strings README.md | grep rshell"

../rshell "strings README.md | grep classes"

../rshell "ls -a | more"

../rshell "cat README.md | wc -l "

../rshell "cat README.md | wc -w"

../rshell "cat README.md | grep classes | wc -l "

../rshell "cat README.md | grep classes | wc -m"

../rshell "ls -a | grep b | wx -c"

../rshell "ls | more"

../rshell "cat < names.txt | tr A-Z a-z | tee test_file1 | tr a-z A-Z > test_file2"

../rshell "ls -a | grep a | grep s"

../rshell "ls -a | grep a | grep a | uniq"

rm test_file1 test_file2 -rf
