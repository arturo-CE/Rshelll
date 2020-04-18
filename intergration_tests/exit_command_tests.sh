#!/bin/sh


../rshell "ls -a; exit; mkdir lab20"
../rshell "ls -a && mkdir lab21 || exit"
../rshell "exit || echo firstfailed && echo passed"
../rshell  "mkdir assn1; exit || ls"
../rshell  "ls || mkdirr lab2 && exit"
../rshell "ls || exit; mkdir assn3"
../rshell  "exit && mkdirr nodir; ls"
../rshell "mkdir assn4 || echoo noecho || exit"
../rshell "ls -a && exit && echo noprint"
../rshell "exit; ls && mkdir success"

rm assn1 assn3 assn4 lab20 lab21 success -rf
