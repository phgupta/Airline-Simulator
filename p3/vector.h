#ifndef VECTOR_H
#define	VECTOR_H
// Author Sean Davis

#include "city.h"

class Vector
{
  City *cityArray;
  int size;
  int count;
  void resize();

public:
  Vector();
  ~Vector();
  void calcDistance(int index1, int index2) const;
  void cleanCities();
  int findAirport(const char *airport) const;
  void readAirports();
  void readCities();
  void calcAirportTraffic() const;
}; // Vector class

#endif	// VECTOR_H 

