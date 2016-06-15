// Author: Sean Davis

#include <iostream>
#include <fstream>
#include <cstring>
#include "vector.h"
using namespace std;

void Vector::calcAirportTraffic() const
{
  char abv[4];
  double passengers = 0;

  cout << "\nPlease enter an airport abbreviation (XXX): ";
  cin >> abv;
  cin.ignore(256, '\n');
    
  int index1 = findAirport(abv);
  
  if (index1 == -1)
    return;

  for (int i = 0; i < count; i++)
  {
    if (index1 == i) continue;
    cityArray[index1].calcTraffic(&cityArray[i], passengers);
  } // calling calcTraffic for every city

  cout << "Total passengers: " << passengers << "\n";
} // calcAirportTraffic()

Vector::Vector()
{
  size = 10;
  count = 0;
  cityArray = new City[size];
}  // initialize()


Vector::~Vector()
{ 
  delete [] cityArray;
}  // deallocate())


void Vector::calcDistance(int index1, int index2) const
{
  cityArray[index1].calcDistance(&cityArray[index2]);
}  // calcDistance()

void Vector::cleanCities()
{
  int i = 0;
  
  while (i < count)
  {
    if (!cityArray[i].hasAirport())
    {
      cityArray[i] = cityArray[--count];
    }  // if city does not have an airport
    else // city has an airport
      i++;
  }  // while more in array
}  // cleanCities())


int Vector::findAirport(const char *airport) const
{
  City city;
  
  city.setAirport(airport);
  
  for (int i = 0; i < count; i++)
    if (cityArray[i].isEqual(&city))
      return i;
  
  cout << airport << " is not a valid airport.\n";
  return -1;
}  // findAirport()


void Vector::readAirports()
{
  char line[1000];
  char state[80];
  City city;
  ifstream fp;
  fp.open("airportLL.txt");

  while (!fp.eof())
  { 
    fp.getline(line, 1000);   
    line[strlen(line) + 1] = '\0';
 
    if (line[0] >= 'A' && line[0] <= 'Z')
    {
      strcpy(state, line);
    } // if line starts with an alphabet
 
    if (line[0] == '[')
    {
      city.readAirport(line, state);
      
      for (int i = 0; i < count; i++)
        if (cityArray[i].isEqual(&city))
        {
          cityArray[i].copyLocation(&city);
          break;
        }  // if found a matching name
      
      city.deallocate();
    }  // if an airport line 
  } // while 
}  // readAirports()


void Vector::readCities()
{ 
  ifstream fp;
  fp.open("citypopulations.csv");
  
  while(!fp.eof())
  {
    if (size == count)
      resize();
  
    cityArray[count++].readCity(fp);
  } // while more in file
  
  --count;
  fp.close();
}  // readCities()


void Vector::resize()
{
  int i;
  City *temp = new City[2*size];
  
  for (i = 0; i < size; i++)
    temp[i] = cityArray[i];
  
  size *= 2;

  delete [] cityArray;
  cityArray = temp;
}  // resize()


