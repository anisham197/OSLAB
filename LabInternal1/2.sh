# Shell script that accepts two file names as arguments, checks if the permission for these files are identical and
#  if the permissions are identical output the common permissions otherwise output each file name followed by its permission.

#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Format: ./2.sh <arg1> <arg2> "
	exit
else
file1=$(ls -l $1 | cut -c2-10)
file2=$(ls -l $2 | cut -c2-10)
	if [ $file1 = $file2 ]; then
		echo "File permissions same: $file1"
	else
		echo "$1 permissions: $file1"
		echo "$2 permissions: $file2"
	fi
fi
