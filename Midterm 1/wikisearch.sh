#!/bin/sh

# Name: Michael Anderson
# Student Email: manderson113@student.gsu.edu

# README: outputs the number of occurences of a given
#         keyword in the file myexamfile.txt
# first argument: keyword to search

count=`grep -iow $1 myexamfile.txt | wc -l`

printf "%s appears %d times in myexamfile.txt\n" $1 $count 
