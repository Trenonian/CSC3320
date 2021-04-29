#/bin/bash

# Name: Michael Anderson
# Student Email: manderson113@student.gsu.edu

phonePattern="^\(([0-9]{3})\)([0-9]{3})-([0-9]{4})$"

read -p "Enter phone number [(999)999-9999]: " phone

if [[ $phone =~ $phonePattern ]]
then
  firstThree=${BASH_REMATCH[1]}
  secondThree=${BASH_REMATCH[2]}
  lastFour=${BASH_REMATCH[3]}
  printf "You entered %s-%s-%s\n" $firstThree $secondThree $lastFour
else
  echo "Invalid Phone Number"
fi
