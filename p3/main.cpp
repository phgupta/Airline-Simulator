// Author: Sean Davis 

#include <iostream>
#include <cstring>
#include "vector.h"
using namespace std;

int getChoice() 
{
  int choice;

  cout << "\nFlight Simulator Menu\n";
  cout << "0. Done.\n";
  cout << "1. Determine distance and passengers between two airports.\n";
  cout << "2. Determine all traffic from one airport.\n";
  cout << "\nYour choice (0 - 2): ";

  cin >> choice;
  cin.ignore(256, '\n');

  if (choice == 0)
  {
    return -1;
  } // if user enters 0 

  else // if user enters 1 or 2
  if (choice == 1 || choice == 2)
  {
    return choice;
  } // if user enters 1 or 2

  else // if user enters wrong number
  {
    cout << "Your choice must be between 0 and 2. Please try again.\n";
    return 0;
  } //if user enters wrong number
} //getChoice()

void run(const Vector *cities)
{
  char airport1[80], airport2[80];
  int index1, index2;
  
  while (1)
  {
    int number = getChoice();

    if (number == 0)
      continue;

    if (number == -1)
      break;

    else // if number is 1
    if (number == 1)
    {
      cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
      cin >> airport1 >> airport2;
     
      index1 = cities->findAirport(airport1);
      index2 = cities->findAirport(airport2);
    
      if (index1 >= 0 && index2 >= 0)
        cities->calcDistance(index1, index2);
    }  // infinite while loop

    else // calculate airport traffic
    if (number == 2)
    {
      cities->calcAirportTraffic();
    } // calculates airport traffic
  } // infinite loop
}  // run())

int main(int argc, char** argv) 
{
  Vector cities;

  cities.readCities();
  cities.readAirports();
  cities.cleanCities();
//  srand(1);
//  for(int i = 0; i < cities.count; i++)
//    printf("%s %s\n", cities.cityArray[i].airport, cities.cityArray[rand() % cities.count].airport);
//  printf("%s %s %lf %lf\n", cities.cityArray[i].name, cities.cityArray[i].airport, cities.cityArray[i].latitude, cities.cityArray[i].longitude);
  run(&cities);
  return 0;
} // main())

