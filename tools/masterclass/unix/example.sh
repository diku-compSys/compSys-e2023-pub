#!/bin/bash

if [[ $# -eq 1 ]] 
then 
	# Count the number of lines that contains "printf"
	cat $1 | grep "printf" | wc -l 
	exit 0
else
	echo 'wrong number of arguments'
	exit 1
fi

