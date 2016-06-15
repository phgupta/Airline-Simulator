#ifndef VECTOR_H
#define VECTOR_H
#include "city.h"

typedef struct
{   
    City* cityArray;
    int size;
    int count;
} Vector;

void initialize(Vector* cities);
void cityPop(Vector* cities);
void readAirports(Vector* cities);
void cleanCities(Vector* cities);
void deallocate(Vector* cities);
void resize(Vector* cities);
int findAirport(const Vector* cities, const char* airport);
void calcDistance(const Vector* cities, int index1, int index2);
void notValidAirport(char* airport1, int index1, char* airport2, int index2);

#endif
