#!/bin/sh

#######################################################################
ARRAY=()
../rshell "[ -d src1231 ]" > result.txt
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
../rshell "[ -e src/main1231.cpp ]" > result.txt
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
../rshell "[ -f src/main1231.cpp ]" > result.txt
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
../rshell "[ -e src/main1.cpp ]" > result.txt
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
../rshell "[ -d src123132123213 ]" > result.txt
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
../rshell "[ 123src/main.cpp ]" > result.txt
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
../rshell "[ -g integration_tests || echo TestFailed ]" > result.txt
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
ARRAY=()
../rshell "[ -d integration_tests ]" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(True)" ]
then
        echo "test failed."

else
        echo "test passed."
fi

rm result.txt
############################################################################

#############################################################################
ARRAY=()
../rshell "[ -h src ]" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(True)" ]
then
        echo "test failed."

else
        echo "test passed."
fi

rm result.txt
############################################################################a

#############################################################################
ARRAY=()
../rshell "[ -i integration_tests ]" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(True)" ]
then
        echo "test failed."

else
        echo "test passed."
fi

rm result.txt
############################################################################
#############################################################################
ARRAY=()
../rshell "[ -d integ_test ]" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(True)" ]
then
        echo "test failed."

else
        echo "test passed"
fi

rm result.txt
############################################################################

#############################################################################
ARRAY=()
../rshell "[ ]" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} == "(True)" ]
then
        echo "test failed."

else
        echo "test passed."
fi

rm result.txt
############################################################################
