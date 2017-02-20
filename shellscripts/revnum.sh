#!/bin/bash
echo -n "Enter number : "
read n
 
# store single digit
sd=0
 
# store number in reverse order
rev=""
 
# store original number
on=$n
 
while [ $n -gt 0 ]
do
    sd=$(( $n % 10 )) # get Remainder 
    n=$(( $n / 10 ))  # get next digit
    # store previous number and current digit in reverse 
    rev=$( echo ${rev}${sd} ) 
done

echo "The reverse of the number is: " $rev