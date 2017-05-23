#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Enter three numbers as arguments"
	exit
else
	if [ $2 -ge $1 ] && [ $2 -ge $3 ]; then
		echo "Max: $2"
	elif [ $3 -ge $1 ] && [ $3 -ge $2 ]; then
		echo "Max: $3"
	else
		echo "Max: $1"
	fi
fi
