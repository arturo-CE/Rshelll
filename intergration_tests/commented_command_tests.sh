#!/bin/sh

../rshell "ls -a # echo hello; mkdir lab20"
../rshell "ls -a && mkdir lab21 # echo noprint"
../rshell "mkderr nolab || echo firstfailed # echo passed"
../rshell "ls -a # mkdirr nodirrr && echo noprint"
../rshell "echo a && echo b #(lsdf0-09sdfosdf09u09dsf()"
../rshell "\"echo \"A #; echo B\" && #echo A"

rm lab21 -rf
