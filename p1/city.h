#ifndef CITY_H
#define CITY_H
#include <stdio.h> 

typedef struct
{  
   double longitude;
   double latitude;
   char* name;
   char* state;
   char airportAbr[4];
   long population;
} City;

void initialize(City* city);
void readCityPop(City* city, FILE* inp);
void readAirport(City* city, char* string);
bool isEqual(const City* city, const City* localCity);
void copyLocation(City* city, const City* localCity);
void deallocate(City* city);
bool hasAirport(City* city);
void setAirport(const City* city, City* localCity);
void calcDistance (const City* city1, const City* city2);
bool isvalidAirport(City* localCity);
void initLocalCity(City* localCity, const char* airport);

#endif
