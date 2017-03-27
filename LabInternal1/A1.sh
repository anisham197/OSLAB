#!/bin/bash
if [ $# -eq 0 ]
then
  echo "Can't have zero arguments!"
  exit
else
  for token in $*
  do
    rev="$token $rev"
  done
  echo $rev
fi
