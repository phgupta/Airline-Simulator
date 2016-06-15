#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include "vector.h"

void run(Vector* cities);

int main(void)
{
  Vector cities;

  initialize(&cities);
  cityPop(&cities);
  readAirports(&cities);
  cleanCities(&cities);
  run(&cities);
  deallocate(&cities);
  return(0);
}//main()

void run (Vector* cities)
{
  int index1, index2;
  int check = 0;
  printf("\n");

  while (check != 1)
  {
    char airport1[80], airport2[80];

    printf ("Please enter two airport abbreviations (XXX XXX = done): ");
    scanf ("%s %s", airport1, airport2);

    if ((strcmp (airport1, "XXX")) == 0 && (strcmp(airport2, "XXX") == 0))
    {
      check = 1;
      break;
    }//Check if the user wants to quit 

    index1 = findAirport (cities, airport1);
    index2 = findAirport (cities, airport2);

    if (index1 == -1 || index2 == -1)
    {
      notValidAirport(airport1, index1, airport2, index2);
    }//If any one of the airports do not exist

    else //If both exist then call calcDistance
      calcDistance(cities, index1, index2);
   }//Infinite loop
}//run()
