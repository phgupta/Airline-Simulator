#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "plane.h"
using namespace std;

Plane::Plane()
{
  name[0] = '\0';
  passengers = 0;
  range = 0;
  speed = 0;
  fuel = 0;
  price = 0;
} // Constructor

ostream& operator << (ostream& os, const Plane& rhs)
{
  os << left << setw(12) << rhs.name;
  os << left << setw(6) << rhs.passengers;
  rhs.putComma(rhs.range); //edit 
  os << left << setw(6) << setprecision(4) << rhs.speed;
  //os << right << setw(2);
  rhs.putComma2(rhs.fuel);
  
  double mpg;
  mpg = double (rhs.range) / double (rhs.fuel);

  os << left << setw(6) << setprecision(3) << mpg;
  os << right << setw(5) << fixed << setprecision(2);
  os << rhs.priceOfFuel * (1 / mpg);
  os << right << setw(2) << "$";
  os << right << setw(5) << fixed << setprecision(1);
  os << double (rhs.price) / 1000000;
  os << endl; 
  return os;
} // operator

Plane Plane::dataInput()
{
  //ofstream fp;
  //fp.open("planes.dat", ios::binary | ios::app);

  Plane tempPlane;

  cout << "Name: ";
  cin >> name;
  strcpy(tempPlane.name, name);
  //fp << name; 
  cout << "Passengers: "; 
  cin >> passengers; 
  tempPlane.passengers = passengers;
  //fp << passengers;
  cout << "Fuel capacity (in U.S. gallons): ";
  cin >> fuel;
  tempPlane.fuel = fuel; 
  //fp << fuel;
  cout << "Range (in miles): ";
  cin >> range; 
  tempPlane.range = range;
  //fp << range;
  cout << "Speed (in mph): ";
  cin >> speed; 
  tempPlane.speed = speed;
  //fp << speed;
  cout << "Price: ";
  cin >> price; 
  tempPlane.price = price;
  //fp << price;
  
  return tempPlane;
} // dataInput()

long Plane::calcTripCost(int *ppl, int *dist) const
{
  long totalCost;

  if (getRange() < *dist)
    totalCost = 0;

  else // else calculate totalcost
  {
    double trips, fuelCost, stdSal, pilotSal, maintCost;

    fuelCost = calcFuelCost(dist);
    stdSal = calcStdSal(dist);
    pilotSal = calcPilotSal(dist);
    maintCost = calcMaintCost(dist);
    trips = calcTrips(ppl);

    totalCost = ceil((fuelCost + stdSal + pilotSal + maintCost)*trips);
  } //calculate totalcost

  return totalCost;
} // calcTripCost()

double Plane::calcFuelCost(int *dist) const
{
  double fuelRange;
  double fuelCost;

  fuelRange = double (fuel) / range;
  fuelCost = fuelRange*(*dist)*priceOfFuel;
  
  return fuelCost;
} // calcFuelCost()

double Plane::calcStdSal(int *dist) const
{
  double std = double (passengers) / 100;
  double cstd = ceil(std);
  double hours = *dist / double (speed);
  double salary = cstd * 30 * ceil(hours + 2);

  return salary; 
} // calcStdSal()

double Plane::calcPilotSal(int *dist) const
{
  double hours = *dist / double (speed);
  double salary = 100 * 2 * ceil(hours + 2);
 
  return salary; 
} // pilotSal()

double Plane::calcMaintCost(int *dist) const
{
  double hours = *dist / double (speed);
  double cost = .000025 * price * hours;

  return cost;
} // calcMaintCost()

double Plane::calcTrips(int *ppl) const
{
  double trip = ceil(double (*ppl) / passengers); 

  return trip; 
} // calcTrips()

char* Plane::getName()
{
  return name;
} // getName()

int Plane::getRange() const
{
  return range;
} // getRange()

void Plane::putComma(int number) const
{
  if (number > 999)
  {
    int thousandth, remainder;

    thousandth = number / 1000;
    remainder = number % 1000;

    if (remainder > 99)
    {
      //cout << left << setw(6);
      cout << thousandth << "," << setw(4) << remainder;
    } // If the remainder is greater than 99

    else // If the remainder is less than or equal to 9 
    if (remainder <= 9)
    {
      //cout << left << setw(6);
      cout << thousandth << ",00" << setw(2) << remainder;
    } // Then print two 0's followed by remainder

    else // If the remainder is less than or equal to 99 
    if (remainder <= 99)// If the remainder is less than or equal to 99
    {
      //cout << left << setw(6);
      cout << thousandth << ",0" << setw(3) << remainder;
    } // Then print 0 followed by remainder
  } // If the number is greater than 999

  else // If the number is less than 999
    cout << setw(4) << number;
} // putComma()

void Plane::putComma2(int number) const
{
  if (number > 999)
  {
    int thousandth, remainder;

    thousandth = number / 1000;
    remainder = number % 1000;

    if (remainder > 99)
    {
      //cout << left << setw(6);
      cout << right << setw(2) << thousandth;
      cout << "," << left << setw(4) << remainder;
    } // If the remainder is greater than 99

    else // If the remainder is less than or equal to 9 
    if (remainder <= 9)
    {
      //cout << left << setw(6);
      cout << right << setw(2) << thousandth;
      cout << ",00" << left << setw(2) << remainder;
    } // Then print two 0's followed by remainder

    else // If the remainder is less than or equal to 99 
    if (remainder <= 99)// If the remainder is less than or equal to 99
    {
      //cout << left << setw(6);
      cout << right << setw(2) << thousandth; 
      cout << ",0" << left << setw(3) << remainder;
    } // Then print 0 followed by remainder
  } // If the number is greater than 999

  else // If the number is less than 999
    cout << setw(4) << number;
} // putComma()
