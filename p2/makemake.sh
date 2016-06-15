#! /bin/bash

#Remove double spaces in the first line

output=$1
shift
option=$#

if [[ $output == *.out ]]
then
	echo -n "$output : " >> Makefile
	find . -type f -name "*.cpp" | sed 's/\.\///g' | tr '\n' ' ' | sed 's/\.cpp/\.o/g' >> Makefile
	echo -ne "\n\tg++ -ansi -Wall -g -o $output $options" >> Makefile
	head -1 Makefile | awk 'BEGIN{files=""}; {for (i=3; i<=NF; i++) files=files$i}; END{printf "%s", files}' | sed 's/\.o/& /g' >> Makefile
else
	echo "Executable name required."
	echo "usage: makemake.sh executable_name"
fi
