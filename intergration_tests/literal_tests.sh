#!/bin/sh

#######################################################################
ARRAY=()
../rshell "test -d ../src1231" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(False)" ]
then
        echo "test passed."


else
        echo "test failed."
fi

rm result.txt
##########################################################################

ARRAY=()
../rshell "test -e ../src/main1231.cpp" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(False)" ]
then
        echo "test passed."

else
        echo "test failed."
fi

rm result.txt
##########################################################################
ARRAY=()
../rshell "test -f ../src/main1231.cpp" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(False)" ]
then
        echo "test passed."

else
        echo "test failed."
fi

rm result.txt
###########################################################################
ARRAY=()
../rshell "test -e ../src/main1.cpp" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(False)" ]
then
        echo "test passed."

else
        echo "test failed."
fi

rm result.txt

##############################################################################
ARRAY=()
../rshell "test -d ../src123132123213" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(False)" ]
then
        echo "test passed."

else
        echo "test failed."
fi

rm result.txt

################################################################################
ARRAY=()
../rshell "test ../123src/main.cpp" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(False)" ]
then
        echo "test passed."

else
        echo "test failed."
fi

rm result.txt

################################################################################
ARRAY=()
../rshell "test -g integration_tests || echo TestFailed" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(False)" ]
then
        echo "test passed."

else
        echo "test failed."
fi

rm result.txt

#############################################################################

#######################################################################
ARRAY=()
../rshell "test -d ../src" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(True)" ]
then
        echo "test passed."


else
        echo "test failed."
fi

rm result.txt
##########################################################################

#######################################################################
ARRAY=()
../rshell "test -e ../src/main.cpp" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(True)" ]
then
        echo "test passed."


else
        echo "test failed."
fi

rm result.txt
##########################################################################

#######################################################################
ARRAY=()
../rshell "test -d ../integration_tests" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(True)" ]
then
        echo "test passed."


else
        echo "test failed."
fi

rm result.txt
##########################################################################

#######################################################################
ARRAY=()
../rshell "test -f ../integration_tests/multiple_commands_tests.sh" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(True)" ]
then
        echo "test passed."


else
        echo "test failed."
fi

rm result.txt
##########################################################################

#######################################################################
ARRAY=()
../rshell "test -f ../prototype/execute.cpp" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(True)" ]
then
        echo "test passed."


else
        echo "test failed."
fi

rm result.txt
##########################################################################
