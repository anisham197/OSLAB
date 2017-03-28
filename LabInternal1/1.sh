#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Correct form ./1.sh <arg1> <arg2> ....."
	exit
else
	for token in $*
	do
		rev="$token $rev"
	done
	echo $rev
fi
