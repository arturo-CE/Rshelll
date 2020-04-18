#!/bin/sh

../rshell "echo \"Output redirection test\" > file_for_testing.txt"
../rshell " cat file_for_testing.txt"

../rshell "ls -a > file_for_testing.txt"
../rshell "cat file_for_testing.txt"

../rshell "ls > file_for_testing.txt"
../rshell "cat file_for_testing.txt"

../rshell "echo pathOutput > file_for_testing.txt"
../rshell "cat file_for_testing.txt"


../rshell "echo \"Output redirection test\" >> file_for_testing.txt"
../rshell "cat file_for_testing.txt"

../rshell "ls -a >> file_for_testing.txt"
../rshell "cat file_for_testing.txt"

../rshell "echo pathOut >> file_for_testing.txt"
../rshell "cat file_for_testing.txt"

../rshell "ls >> file_for_testing.txt"
../rshell "cat file_for_testing.txt"

../rshell "exit"

rm file_for_testing.txt -rf
