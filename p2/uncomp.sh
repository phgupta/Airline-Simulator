#! /bin/bash

# Uncompressing files 

max=$#

if [[ $# -gt 0 ]]; then
	for((i=1;i<=max;i++)); do
	if [[ $i == *.tar || $i == *.tar.gz || $i == *.tgz || $i == *.tar.Z || $i == *.gz || $i == *.Z ]]; then
		tar -xf $i

	elif [[ $i == *.zip ]]; then
		unzip -q $i 

	else 
		echo "Put acceptable file extension"
		#Exit program  
	fi
	done
else 
	echo "Arguments should be greater than 1"
fi
