#! /bin/bash

directory=$1
pattern=$2
shift
shift
options=$@

if [[ -d $directory ]]
then
	if [[ -n $pattern ]]
	then
		if [[ $1 != " " ]]
		then
			if [[ $options =~ ^(-[ilnvx]+ ?)+$ ]]
			then
				echo "works"
				grep -r $options $pattern $directory
			else
				echo "usage: grepdir.sh directory pattern [-grep option]*"
			fi 
		else
			grep -r $pattern $directory
		fi
	else 
		echo "usage: grepdir.sh directory pattern [-grep option]*"
	fi
else
	echo "usage: grepdir.sh directory pattern [-grep option]*"
fi
