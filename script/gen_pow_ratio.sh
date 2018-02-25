#!/bin/bash
DIR=./
ID_BEGIN=0
FILE_NUM=10
POWER=4
PERCENT=50
PROGRAM=a.out
if [ "$1" != "" ] ; then
	DIR=$1
	echo "set DIR to ${DIR}."
fi
if [ "$2" != "" ] ; then
	ID_BEGIN=$2
	echo "set ID_BEGIN to ${ID_BEGIN}."
fi
if [ "$3" != "" ] ; then
	FILE_NUM=$3
	echo "set FILE_NUM to ${FILE_NUM}."
fi
if [ "$4" != "" ] ; then
	POWER=$4
	echo "set POWER to ${POWER}."
fi
if [ "$5" != "" ] ; then
	PERCENT=$5
	echo "set PERCENT to ${PERCENT}."
fi

END=$(( $ID_BEGIN + $FILE_NUM - 1))

for ID in $( seq $ID_BEGIN $END );
do
	echo "$ID"
	./$PROGRAM $POWER $PERCENT ${DIR}/${ID}_
done

