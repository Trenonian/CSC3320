# bookmanager.sh

Use the following commands to manage the phonebook

(a)dd firstName lastName 999-999-9999 address

(r)emove 999-999-9999

(u)pdate 999-999-9999

(f)ind searchText

(i)mport filename.csv

(h)elp

# compressor.sh

Compresses all files in a given directory that have not been accessed for an input number of days

compressor -r directory fullDaysSinceAccessed

-r is optional, makess it recursively apply

directory . = current directory

directory ~ = root directory

0 days means all files will be compressed

will not attempt to compress .gz files

will not compress files with this script's name 

# factorial.c

takes a positive integer as the first argument

prints its factorial

# funMath.sh

a shell script that uses an inputed number to execute the c programs factorial and processNumber

# helpme.sh

takes a unix command as the first argument, displays the manual for it, or prints a failure message if the command isn't in mandatabase.txt

(F)orward, (B)ack, (Q)uit


# processNumber.c

takes an integer as the first argument, then prints the results of a series of calculations:

* the sum of it left-shifted 3 times and it's complement

* the decimal->binary conversion

* the binary->decimal conversion, if possible

# shiftComplement.c

takes an integer as the first argument, then prints the sum of it left-shifted 3 times and it's complement

# wikisearch.sh

outputs the number of occurences of a given keyword in the file myexamfile.txt

first argument: keyword to search