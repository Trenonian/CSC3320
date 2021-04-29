#!/bin/sh

# Name: Michael Anderson
# Student Email: manderson113@student.gsu.edu

# README: compressor -r directory fullDaysSinceAccessed
#         -r is optional, makess it recursively apply
#         directory . = current directory
#         directory ~ = root directory
#         0 days means all files will be compressed
#         will not attempt to compress .gz files
#         will not compress files with this script's name 

myName=`basename $0`

depth="-maxdepth 1"
if [[ $1 == '-r' ]]
then
  depth=""
  shift
fi

days=`expr $2 - 1`

if [[ -z $1 ]]
then
  echo "Please enter a valid directory"
  exit 128
fi

if [[ -z $2 || $2 -lt 0 ]]
then
  echo "Please enter a valid number of days"
  exit 128
fi

fileList=`find $1 $depth -type f -atime +$days | grep -v '\.gz$' | grep -v $myName`

for file in $fileList
do
  echo "Compressing" $file
  gzip $file
done
