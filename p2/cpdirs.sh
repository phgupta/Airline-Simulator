#! /bin/bash

if [[ $# -gt 3 || $# -lt 3 ]]
then
	echo "usage: cpdirs.sh source_directory1 source_directory2 dest_directory"
else 
	if [[ -d $1 ]]
	then
		if [[ -d $2 ]] 
		then
			if [[ -f $3 ]]
			then
				echo "usage: cpdirs.sh source_directory1 source_directory2 dest_directory"
			else
				if [[ -d $3 ]]
				then
					cp -u $1/* $2/* $3
				else
					mkdir $3
					cp -u $1/* $2/* $3
				fi
			fi
		else
			echo "usage: cpdirs.sh source_directory1 source_directory2 dest_directory"
		fi
	else
		echo "usage: cpdirs.sh source_directory1 source_directory2 dest_directory"
	fi
fi
