#Shell script that accepts valid login names as arguments and prints their corresponding home directories
#  if no arguments are specified, print a suitable error message.

#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Format: ./3.sh <arg1> <arg2> ....."
	exit
else
	for user in $*
	do
	if [ -d $(eval echo ~$user) ]; then
		echo "User: $user  Home Directory: $( eval echo ~$user)"
	else
		echo "Invalid login name $user"
	fi
done
fi
