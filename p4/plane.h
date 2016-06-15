#ifndef PLANE_H
#define PLANE_H
#include <iostream>
using namespace std;

class Plane
{

private:

  static const double priceOfFuel = 3.39;
  char name[12];
  int passengers;
  int range;
  int speed;
  int fuel;
  int price;

  friend ostream& operator << (ostream& os, const Plane& rhs); 

public :

  Plane();
  Plane dataInput();
  long calcTripCost(int *ppl, int *dist) const;
  double calcFuelCost(int *dist) const;
  double calcStdSal(int *dist) const;
  double calcPilotSal(int *dist) const;
  double calcMaintCost(int *dist) const;
  double calcTrips(int *ppl) const;
  char* getName();
  int getRange() const;
  void putComma(int number) const;
  void putComma2(int number) const;
}; // class Plane

#endif // PLANE_H