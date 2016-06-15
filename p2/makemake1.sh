# shell script creates makefile for all .cpp files in current directory

var=`echo $#`
string=' '


for file in *.cpp;do
string+=${file%.cpp*}'.o '
done

if ((var==0)); then
        echo Executable name required.
        echo usage: makemake.sh executable_name

elif((var==1));then


        echo $1 : $string > Makefile
        echo '	'g++ -ansi -Wall -g -o $1  $string  >> Makefile
        echo >> Makefile
        for file in *.cpp;do
                if (grep -q '#include' $file); then
                        header=$(awk -F\" '/#include/ {print $2}' $file)
                       echo ${file%.cpp*}.o : $file $header >> Makefile
                       echo '	'g++ -ansi -Wall -g -c $cmdstr $file >> Makefile
                       echo >> Makefile
                else

                        echo ${file%.cpp*}.o : $file >> Makefile
                        echo '	'g++ -ansi -Wall -g -c $file  >> Makefile
                        echo >> Makefile
                fi
        done

        echo clean : >> Makefile
        echo -n '	'rm -f $1 $string >> Makefile

else

        cmdstr=' ';
        for ((i=2;i<=var;i++));do
        cmdstr+=${!i}' '
        done

        echo $1 : $string > Makefile
        echo '	'g++ -ansi -Wall -g -o $1 $cmdstr $string >> Makefile
        echo >> Makefile
        for file in *.cpp;do
                if (grep -q '#include' $file); then
                        header=$(awk -F\" '/#include/ {print $2}' $file)
                        echo ${file%.cpp*}.o : $file $header >> Makefile
                        echo '	'g++ -ansi -Wall -g -c $cmdstr $file  >> Makefile
                        echo >> Makefile
                else
                        echo ${file%.cpp*}.o : $file >> Makefile
                        echo '	'g++ -ansi -Wall -g -c $cmdstr $file  >> Makefile
                        echo >> Makefile
                fi
        done

        echo clean : >> Makefile
        echo -n '	'rm -f $1 $string >> Makefile

fi
