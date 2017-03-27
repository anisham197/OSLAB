#!/bin/bash

echo "Enter the directory name: "
read dir1

if [ ! -d $dir1 ]
  then
	echo "Invalid directory!"
	exit
fi

large=0
#Finds all files recursively in the directory

for file1 in `find $dir1 -type f`
	do
		#Gets the size and allots it to "large" if it is the largest
		size1=`stat -c %s $file1`
		echo "Size of $file1 is: $size1"
		if [ $size1 -gt $large ]
      then
			large=$size1
			lar_file=$file1
	  fi
  done
echo "The largest file is: $lar_file"
echo "And its size is: $large"
