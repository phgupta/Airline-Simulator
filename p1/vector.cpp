#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "city.h"

void initialize(Vector* cities)
{
  int i;
  cities->size = 10;
  cities->count = 0;
  cities->cityArray = NULL;
  cities->cityArray = (City*) malloc(sizeof(City)*10);

  for (i = 0; i < 10; i++)
  {
    initialize(&cities->cityArray[i]);
  }//initializing the cityArray

  return;
}//initialize()

void cityPop(Vector* cities)
{
  FILE* inp;
  inp = fopen("citypopulations.csv", "r");

  while (!feof(inp))
  {
    if (cities->count == cities->size)
    {
      resize(cities);
      //cities->count = cities->count + 1;
    }//Checks if number of cities is equal to the current size

    readCityPop(&cities->cityArray[cities->count], inp);
    cities->count = cities->count + 1;
  }//Call readCityPop() till end of file 

  //cities->count -= cities->count; 
  fclose(inp);
  return;
}//cityPop()

void resize(Vector* cities)
{
  int i;
  City* tempCity = NULL;

  tempCity = (City*) malloc(sizeof(City)*cities->count);
  cities->size = cities->size * 2;

  for (i = 0; i < cities->count; i++)
  {
    tempCity[i] = cities->cityArray[i];
  }//copies upper half into tempCity
  
  free(cities->cityArray);
  cities->cityArray = NULL;
  cities->cityArray = (City*) malloc(sizeof(City) * cities->size);

  for (i = 0; i < cities->size; i++)
  {
    if (i < cities->count)
    {
      cities->cityArray[i] = tempCity[i];
    }//copying upper half into cityArray

    else //when i is greater than noOfCities
    {
      initialize(&cities->cityArray[i]);
    }//when i is greater than noOfCities
  } //resizing

  free(tempCity);
}//resize()

void readAirports(Vector* cities)
{
  FILE* inp;
  inp = fopen("airportLL.txt", "r");
  int i;

  while (!feof(inp))
  {
    char string[80];
    int size = 80;
    City localCity;
    initialize(&localCity);

    fgets(string, size, inp);

    if (string[0] == '[')
    {
      readAirport(&localCity, string);

      for (i = 0; i < cities->count - 1; i++)
      {
        if (isEqual(&cities->cityArray[i], &localCity))
        {
          copyLocation(&cities->cityArray[i], &localCity);
          break;
        }//checks if the two cities are equal or not
      }//Comparing all city names
    }//If the line is an airport
  }//Till end of file is reached

  fclose(inp);
  return;
}//readAirports()

void cleanCities(Vector* cities)
{
  int i = 0;

  while (i < cities->count)
  {
    if (!hasAirport(&cities->cityArray[i]))
    {
      deallocate(&cities->cityArray[i]);
      cities->cityArray[i] = cities->cityArray[(cities->count)-1];
      cities->count -= 1;
    }//Checks if it has an airport or not
    else //else increment i
      i++;
  }//loops until i reaches number of cities
}//cleanCities()

void deallocate(Vector* cities)
{
  int i;

  for (i = 0; i < cities->size; i++)
  {
    deallocate(&cities->cityArray[i]);
  }//deallocating all the cities

  free(cities->cityArray);
  return;
}//deallocate())

int findAirport(const Vector* cities, const char* airport)
{
  City localCity;
  initialize(&localCity);
 
  initLocalCity(&localCity, airport);

  for ( int i = 0; i < cities->count; i++)
  {
    setAirport(&cities->cityArray[i], &localCity);

    if (isvalidAirport(&localCity))
    {
      return i;
    }//Checks if the airport is valid or not
  }//loops through the entire cityarray

  deallocate (&localCity);
  return -1;
}//findAirport()

void calcDistance(const Vector* cities, int index1, int index2)
{
  calcDistance(&cities->cityArray[index1], &cities->cityArray[index2]);
}//calcDistance()

void notValidAirport(char* airport1, int index1, char* airport2, int index2)
{
  if (index1 == -1 && index2 == -1)
  {
    printf("%s is not a valid airport.\n", airport1);
    printf("%s is not a valid airport.\n\n", airport2);
  }//checks if index1 and index2 both are 0

  else //if only index1 is 0
  if (index1 == -1)
  {
    printf("%s is not a valid airport.\n\n", airport1);
  }//print error statement

  else //if only index2 is 0
    printf("%s is not a valid airport.\n\n", airport2);
}//notValidAirport()
