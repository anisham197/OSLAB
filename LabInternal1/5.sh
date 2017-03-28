#!/bin/bash

stty -echo
echo "Enter Password"
read pass1
echo "Confirm Password"
read pass2

if [ $pass1 = $pass2 ]; then
	echo "Terminal is locked"
	trap '' 2 3 15
	while true
	do
		echo "Enter Password"
		read pass3
		if [ $pass3 = $pass1 ]; then
			echo "Terminal Unlocked"
			stty echo
			exit
		else
			echo "Wrong Password, Try Again"
		fi
	done
else
	echo "Password Mismatch"
	stty echo
fi
