#/bin/bash
# Name: Michael Anderson
# Student Email: manderson113@student.gsu.edu
echo "Welcome to the world of Computer Science!"
printf "Today's date is %s\n" $(date +%F)
echo -n "Directories in /home: "
ls -l | grep "^d" | wc -ls
printf "PATH: %s\nUSER: %s\nSHELL: %s\n" $PATH $USER $SHELL
echo -n "Disk usage: "
df --total | tail -1 | awk '{print $3}'
printf "Please, could you loan me \$25.00?\n"
printf "if x = 2, x * x = 4, x / 2 = 1\n"
echo "All .sh files here that start with 'c':"
ls *.sh | grep --color=never '^c' | awk '{printf "  %s\n", $0}'
printf "Good bye, btw the current hour is %s\n" $(date +%H)