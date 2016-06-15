#ifndef CITY_H
#define	CITY_H
// Author: Sean Davis
#include <iostream>
#include <fstream>
using namespace std;

class City
{
  double longitude;
  double latitude;
  char *name;
  char *state;
  char airport[4];
  int population;

public : 

  City();
  ~City();
  void deallocate();
  City& operator = (const City& rhs);
  void calcDistance(const City *city2) const;
  void copyLocation(const City *srcCity);
  bool hasAirport();
  bool isEqual(const City *city2) const;
  void readAirport(char *line, char *stat);
  void readCity(ifstream& fp);
  void setAirport(const char *airport); 
  void calcTraffic(const City *city2, double &passengers);
}; // City class

#endif	// CITY_H 

