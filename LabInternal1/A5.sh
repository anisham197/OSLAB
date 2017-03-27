#!/bin/bash
stty -echo
echo "Enter the password: "
read pass1
echo "Confirm the password: "
read pass2

if [ $pass1 = $pass2 ]
	then
	echo "The terminal is locked!"
	trap '' 2 3 15
	while true
	do
		echo "Enter the password: "
		read pass3
		if [ $pass3 = $pass2 ]
			then
			echo "The terminal is unlocked!"
			stty echo
			exit
		else
			echo "Incorrect password! Try again."
		fi
	done
else
	echo "Passwords do not match!"
	stty echo
fi
