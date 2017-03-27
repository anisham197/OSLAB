#!/bin/bash
if [ $# -eq 0 ]
then
  echo "Can't have zero arguments!"
  exit
else
	for login in $*
	do
		usr=`cut -d ":" -f 1 /etc/passwd | grep $login`
		if [ ${#usr} -ne 0 ]
		then
			echo "Login Name: $login"
			dir=`grep $login /etc/passwd | cut -d ":" -f 6`
			echo "Home Directory: $dir"
		else
			echo "$login is not a valid login id!"
		fi
	done
fi
