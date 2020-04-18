#!/bin/sh

#######################################################################
ARRAY=()
../rshell "(echo a && echo b) || (echo c && echo d)" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} != a ]
then
        echo "test failed."
fi

if [ "${ARRAY[1]}" != b ]
then
        echo "test failed."
fi

if [ ${#ARRAY[@]}  == 2 ]
then
        echo "test passed."
else
        echo "test failed."
fi

rm result.txt
##########################################################################

ARRAY=()
../rshell "(echo a && echo b) && (echo c && echo d)" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} != a ]
then
        echo "test failed."
fi

if [ "${ARRAY[1]}" != b ]
then
        echo "test failed."
fi

if [ ${ARRAY[2]} != c ]
then
        echo "test failed."
fi

if [ ${ARRAY[3]} != d ]
then
        echo "test failed."
fi

if [ ${#ARRAY[@]} == 4 ]
then
        echo "test passed."
else
        echo "test failed."
fi

rm result.txt
##########################################################################

ARRAY=()
../rshell "( echo a && echo b || (echo e && echo f) )" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} != a ]
then
        echo "test failed."
fi

if [ "${ARRAY[1]}" != b ]
then
        echo "test failed."
fi

if [ ${#ARRAY[@]} == 2 ]
then
        echo "test passed."
else
        echo "test failed."
fi

rm result.txt
##########################################################################

ARRAY=()
../rshell "( echo a && echo b || (echo e && echo f) ) && (echo c && echo d)" > result.txt
while read foo; do
        ARRAY+=($foo)
done < result.txt

if [ ${ARRAY[0]} != a ]
then
        echo "test failed."
fi

if [ "${ARRAY[1]}" != b ]
then
        echo "test failed."
fi

if [ ${ARRAY[2]} != c ]
then
        echo "test failed."
fi

if [ "${ARRAY[3]}" != d ]
then
        echo "test failed."
fi

if [ ${#ARRAY[@]} == 4 ]
then
        echo "test passed."
else
        echo "test failed."
fi

rm result.txt
##########################################################################
