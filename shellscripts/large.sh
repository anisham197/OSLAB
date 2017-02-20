#!/bin/bash

echo "Enter 3 numbers:"
echo "a:"
read a
echo "b:"
read b
echo "c:"
read c

if [ $a -gt $b ] ; then
    if [ $a -gt $c ] ; then
        echo -e "$a is greatest"
    else
        echo -e "$c is greatest"
    fi
else   
    if [ $b -gt $c ] ; then
        echo -e "$b is greatest"
    else
        echo -e "$c is greatest"
    fi
fi