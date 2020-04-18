#!/bin/sh

../rshell "ls -a; echo hello; mkdir lab20"
../rshell "ls -a && mkdir lab21 || echo noprint"
../rshell "mkderr nolab || echo firstfailed && echo passed"
../rshell "ls -a && mkdirr nodirrr && echo noprint"
../rshell "\"A && exit\" && echo A || exit"
../rshell "echo \"<text>\" && \"echo A || echo B || echo C && ls -j && echo A && ls -j && echo A || echo B"
../rshell "echo AB CD && echo \"echo echo ; echo echo\""
rm lab20 lab21 -rf

