#!/bin/sh


../rshell ls -a

../rshell "mkdir goat"

../rshell "echo helllo"

../rshell "echo world"

../rshell "git status"

../rshell "ls -a"

../rshell "echo \"madelab\""

../rshell "mkdir goat1"

../rshell "mkdir goat2"

../rshell "ls"

../rshell "echo single_commands"

../rshell "exit"

rm goat goat1 goat2 -rf
