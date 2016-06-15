#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "city.h"

void initialize(City* city)
{
  city->longitude = 0;
  city->latitude = 0;
  city->name = NULL;
  city->state = NULL;
  city->airportAbr[0] = '\0';
  city->population = 0;
  return;
}//initialize()

void readCityPop(City* city, FILE* inp)
{
  char* token;
  char string[80];
  int size = 80;

  if (fgets(string, size, inp) != NULL)
  {
    token = strtok(string, ",");
    city->name = (char*) malloc(strlen(token) + 1);
    strcpy(city->name, token);
    //city->name[strlen(token)] = '\0';

    token = strtok(NULL, ",");
    city->state = (char*) malloc(strlen(token) + 1);
    strcpy(city->state, token);
    //city->state[strlen(token)] = '\0';
    city->population = atoi(strtok(NULL, ""));
  }//Reads in each line from citypopulations.csv

  return;
}//readCityPop()

void readAirport(City* city, char* string)
{
  char* token;
  int i;

  token = strtok(string, " ");

  for (i = 0; i < 4; i++)
  {
    token[i] = token[i + 1];
  }//Removing the []

  token[i-1] = '\0';

  strcpy(city->airportAbr, token);
  city->latitude = atof(strtok(NULL, " "));
  city->longitude = atof(strtok(NULL, " "));

  token = strtok(NULL, ",");
  token++;
  city->name = (char*) malloc(strlen(token) + 1);
  strcpy(city->name, token);

  return;
}//readAirport()

bool isEqual(const City* city, const City* localCity)
{
  if (strcmp(city->airportAbr, localCity->airportAbr) == 0)
  {
    return true;
  }//Comparing airport name

  else //Comparing city name
  if (strcmp(city->name, localCity->name) == 0)
  {
    return true;
  }//Comparing city names

  else //else return false
  {
    return false;
  }//else return false
}//isEqual()

void copyLocation(City* city, const City* localCity)
{
  city->latitude = localCity->latitude;
  city->longitude = localCity->longitude;
  strcpy(city->airportAbr, localCity->airportAbr);
  return;
}//copyLocation()

void deallocate(City* city)
{
  free(city->name);
  free(city->state);
  return;
}//deallocate()

bool hasAirport(City* city)
{
  if (city->airportAbr[0] != '\0')//Returns true if city has an airport
    return true;

  else //Else returns false
    return false;
}//hasAirport()

void setAirport(const City* city, City* localCity)
{
  if (isEqual(city, localCity))
  {
    free (localCity->name);
    int cityName = (strlen (city->name) + 1);
    int stateName = (strlen (city->state) + 1);

    localCity->name = (char*) malloc (sizeof(char)*cityName);
    strcpy (localCity->name, city->name);

    localCity->state = (char*) malloc (sizeof(char)*stateName);
    strcpy (localCity->state, city->state);

    localCity->population = city->population;
    localCity->longitude = city->longitude;
    localCity->latitude = city->latitude;
   }//Checks if the cities are equal or not
}//setAirport()

void calcDistance (const City* city1, const City* city2)
{
  int R = 3963;
  double long1 = (city1->longitude / 180)*M_PI;
  double long2 = (city2->longitude / 180)*M_PI;
  double lat1 = (city1->latitude / 180)*M_PI;
  double lat2 = (city2->latitude / 180)*M_PI;
  double pop;

  double sinPhi = sin(lat1) * sin(lat2);
  double cosPhi = cos(lat1) * cos(lat2);
  double cosGamma = cos(long1 - long2);

  double distance = acos (sinPhi + cosPhi * cosGamma) * R;

  if (distance < 100)
  {
    pop = 0;
  }//If distance < 100, then population = 0

  else //else calculate population
  {
    pop = ((double)city1->population * city2->population) / 250000000;
  }//else calculate population

  printf ("%d passengers fly the %d miles from\n", (int)pop, (int)distance);
  printf("%s,%s to ", city1->name, city1->state);
  printf("%s,%s\n\n", city2->name, city2->state);
}//calcDistance()

bool isvalidAirport(City* localCity)
{
  if (strcmp(localCity->name, "NULL") == 0)
  {
    return false;
  }//Checks if name is null

  else //if not then return true
    return true;
}//validAirport()

void initLocalCity(City* localCity, const char* airport)
{
  strcpy (localCity->airportAbr, airport);
  localCity->name = (char*) malloc(5*sizeof(char));
  strcpy (localCity->name, "NULL");   
}//initLocalCity()
