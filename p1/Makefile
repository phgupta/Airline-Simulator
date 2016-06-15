simulator.out : main.o vector.o city.o
	g++ -g -Wall -ansi -o simulator.out main.o vector.o city.o

main.o : main.cpp vector.h
	g++ -g -Wall -ansi -c main.cpp

vector.o : vector.cpp vector.h city.h
	g++ -g -Wall -ansi -c vector.cpp

city.o : city.cpp city.h
	g++ -g -Wall -ansi -c city.cpp 

clean : 
	rm -f simulator.out *.o
