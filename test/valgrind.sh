#!/bin/bash

EXEC=./minishell # Put your executable's path here.
LOG=valgrind

# Compile and set executable rights
make debug -C ../
cp ../minishell .
chmod 755 minishell

valgrind \
	--tool=memcheck \
	--leak-check=full \
	--leak-resolution=high \
	--track-origins=yes \
	--show-reachable=yes \
<<<<<<< HEAD
	--suppressions=/mnt/nfs/homes/hlucie/Documents/minishell/test/minimal.supp \
=======
	--suppressions=/mnt/nfs/homes/ehautefa/Desktop/minishell/test/minimale.supp \
>>>>>>> main
	--log-file=${LOG}.log \
	$EXEC $@ \
;

# cat valgrind.log | ./suppressions.sh > minimale.supp
#--gen-suppressions=all \

# Separate the logs from multiple processes into multiple log files.
grep '==[0-9]*==' <valgrind.log --only-matching | sort --unique | tr -d = |
	while read -r pid; 
	do \
		pidlog=${LOG}.${pid}.log;
		echo $pidlog;
		grep "$pid" <${LOG}.log >$pidlog;
		grep -A1 "valgrind" $pidlog | grep $EXEC;
	done;
