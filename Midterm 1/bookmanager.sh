#!/bin/bash
# Name: Michael Anderson
# Student Email: manderson113@student.gsu.edu

# README: Command List
#         phoneNumber format: 999-999-9999, optional '-'
#         (a)dd firstName lastName phoneNumber address
#         (r)emove phoneNumber
#         (u)pdate phoneNumber 
#         (f)ind searchText
#         (i)mport filename.csv
#         (h)elp

validName="^[A-Z][-'A-z]+$"
validNumber="^\(?([0-9]{3})\)?-?([0-9]{3})-?([0-9]{4})$"
validJustNumbers="^[0-9]{10}$"

validate() {
 if [[ !$firstName =~ $validName || !$lastName =~ $validName || !$phoneNumber =~ $validJustNumbers ]]
 then
  echo 'invalid input'
  return 1
 fi
 if !(checkDuplicate)
 then
  echo 'duplicate number, discarding input'
  return 1
 fi
 return 0
}

checkDuplicate() {
 duplicate=$(grep $phoneNumber phonebook)
 if [[ -n $duplicate ]]
 then
  return 1
 fi
 return 0
}

SORTED=true

action=$1; shift

if [[ $action =~ ^a ]]
then # add
 firstName=$1; shift
 lastName=$1; shift
 phoneNumber="${1//[!0-9]/}"; shift
 address="$*"
 if validate
 then
  printf 'adding:\n'
  printf "%s %s %s  %s\n" $firstName $lastName $phoneNumber "$address"
  printf "%-16s %-16s %s  %s\n" $firstName $lastName $phoneNumber "$address" >> phonebook
 SORTED=false
 else
  echo 'add failed'
 fi
elif [[ $action =~ ^r ]]
then # remove
 phoneNumber="${1//[!0-9]/}"; shift
 if [[ $phoneNumber =~ $validNumber ]]
 then
  lineToRemove=$(grep -w $phoneNumber phonebook)
  if [[ -n $lineToRemove ]]
  then
   echo "Removing:"
   echo $lineToRemove
   sed -i "/$phoneNumber/d" phonebook
  else
   echo "Number not in phonebook"
  fi
 fi
elif [[ $action =~ ^u ]]
then # update
 phoneNumber="${1//[!0-9]/}"; shift
 if [[ !$phoneNumber =~ $validNumber ]]
 then
  echo "invalid phone number"
 else
  match=$(grep -w $phoneNumber phonebook)
  lineCount=$(echo "$match" | wc -l)
  if [[ $lineCount=="1" ]]
  then
   read -p "Enter their first name: " firstName
   read -p "Enter their last name: " lastName
   read -p "Enter their address: " address
   sed -i "/$phoneNumber/d" phonebook
   echo "updated:"
   printf "%s %s %s  %s\n" $firstName $lastName $phoneNumber "$address"
   printf "%-16s %-16s %s  %s\n" $firstName $lastName $phoneNumber "$address" >> phonebook
   SORTED=false
  else
   echo "Number not in phonebook"
  fi
 fi
elif [[ $action =~ ^f ]]
then # find
 search="$*"
 if [[ $search =~ $validNumber ]]
 then
  search="${search//[!0-9]/}" 
 else
  search="${search// / \{1,\}}"
 fi
 results=$(grep -i "$search" phonebook)
 if [[ -n $results ]]
 then
  echo "$results"
 else
  echo "No Results"
 fi
elif [[ $action =~ ^i ]]
then
 fileName=$1; shift
 cat $fileName | while read line
 do
  entryMatch="^(.*),(.*),([0-9]{3})-([0-9]{3})-([0-9]{4}),\"(.*)\"$"
  if [[ $line =~ $entryMatch ]]
  then
   firstName=${BASH_REMATCH[1]}
   lastName=${BASH_REMATCH[2]}
   pA=${BASH_REMATCH[3]}
   pB=${BASH_REMATCH[4]}
   pC=${BASH_REMATCH[5]}
   phoneNumber="$pA$pB$pC"
   address=${BASH_REMATCH[6]}
   exists=$(grep $phoneNumber phonebook)
   if [[ -z $exists ]]
   then
    printf "%-16s %-16s %s  " $firstName $lastName $phoneNumber >> phonebook
    echo $address >> phonebook
   fi
  fi
 done
 SORTED=false
elif [[ $action == "" || $action =~ "^h" ]]
then # help
 echo "(a)dd firstName lastName 999-999-9999 address" 
 echo "(r)emove 999-999-9999" 
 echo "(u)pdate 999-999-9999" 
 echo "(f)ind searchText"
 echo "(i)mport filename.csv"
else # invalid command
 echo "invalid command"
fi
if [[ $SORTED == false ]]
then
 sort -o phonebook -k2b,2 -k1,1 phonebook
fi
