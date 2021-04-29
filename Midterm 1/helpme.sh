#!/bin/bash

# Name: Michael Anderson
# Student Email: manderson113@student.gsu.edu

# README: enter the command in lowercase
#         (F)orward, (B)ack, (Q)uit

indexes=`egrep -n "^[A-Z]+\(1\)" mandatabase.txt | sed -n "s/\([0-9]\+\):\([A-Z]\+\).*/\2 \1/p" | tr '[A-Z]' '[a-z]'`

read -p "Type in a command to see it's manual: " command

pattern=".*[0-9]*\s*$command\s([0-9]+)\s*[a-z]*\s*([0-9]*)"

if [[ $indexes =~ $pattern ]]
then
  firstLine=${BASH_REMATCH[1]}
  lastLine=${BASH_REMATCH[2]}
  ((lastLine--))
  head -n$lastLine mandatabase.txt | tail -n+$firstLine | less
else
  echo "sorry, I cannot help you"
fi
