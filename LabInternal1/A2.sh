#!/bin/bash

#Less than two arguments error
if [ $# -ne 2 ]
	then
	echo "Incorrect number of arguments!"
	exit

else
	#Cut the permissions between 2-10 in the ls -l command using piping
	f1=`ls -l $1 | cut -c2-10`
	f2=`ls -l $2 | cut -c2-10`

	if [ $f1 = $f2 ]
		then
		echo "File permissions are equal!"
		echo  $f1
	else
		echo "File permissions are not equal!"
		echo "Permissions of $1: $f1"
		echo "Permissions of $2: $f2"
	fi
fi
