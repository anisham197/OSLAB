#!/bin/bash
echo "Enter a string"
read str
reverse=$(echo $str | rev)
echo $reverse
