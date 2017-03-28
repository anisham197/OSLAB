#!/bin/bash

function max_size {
	if [ ! -d $1 ]; then
		echo "Invalid Directory"
		exit
	else
		max=0
		for file in $(find $1 -type f)
		do
			fsize=$(stat -c %s $file)
			if [ $fsize -ge $max ]; then
				max=$fsize
				max_file=$file
			fi
		done
		echo "$max_file : $max"
	fi
}

echo "Enter Parent Directory: "
read dir
max_size $dir
