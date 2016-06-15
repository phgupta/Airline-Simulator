// Author: Sean Davis 

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <climits>
#include <iomanip>
#include "vector.h"
#include "plane.h"
using namespace std;

void addPlaneInformation(Plane *planes, int *tracker)
{ 
  Plane temp;
  ofstream fp("planes.dat", ios::app | ios::binary);
  temp = planes[*tracker].dataInput();
  fp.write((char*)&temp, sizeof(Plane));
  fp.close();
  *tracker = *tracker + 1;
  return;
} // addPlaneInformation()

void calcDistance(const Vector *cities, int *ppl, int *dist, int* opt)
{
  char airport1[80], airport2[80];
  int index1, index2;
  cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
  cin >> airport1 >> airport2;
  index1 = cities->findAirport(airport1);
  index2 = cities->findAirport(airport2);

  if (index1 >= 0 && index2 >= 0)
    cities->calcDistance(index1, index2, ppl, dist, opt);
}  // calcDistance()

void output5(int *ppl, int *dist, int n, char *planeName, long cheapCost)
{
  cout << left << setw(11) << "Passengers";
  cout << left << setw(7) << "Miles"; // approx
  cout << left << setw(6) << "Trips";
  cout << left << setw(10) << "Name"; // approx
  cout << left << setw(5) << "Cost\n"; // approx
  cout << left << setw(11) << *ppl;
  cout << left << setw(7) << *dist;
  cout << left << setw(6) << n;
  cout << left << setw(10) << planeName;
  cout << "$";
  cout << left << cheapCost << endl; 

  return;
} // output5()

void determineBestPlane(Plane *planes, int *track, const Vector *cities)
{ 
  char *ptr, *planeName;
  int ppl = 0, dist = 0, opt = 5, planeNum = -1, intmax = INT_MAX;
  long tripCost = 0;
 
  calcDistance(cities, &ppl, &dist, &opt);
  
  for (int i = 0; i < *track; i++)
  {
    tripCost = planes[i].calcTripCost(&ppl, &dist);

    if (tripCost > 0 && tripCost < intmax)
    {
      intmax = tripCost;
      planeNum = i;
    } // calculates the airport with the cheapest cost
  } // calcTripCost for all planes

  if (planeNum == -1)
    cout << "No planes available\n";

  else // If plane is available  
  {
    int numberOfTrips = planes[planeNum].calcTrips(&ppl);
    ptr = planes[planeNum].getName();
  
    planeName = new char[strlen(ptr) + 1];
    strcpy(planeName, ptr);
  
    output5(&ppl, &dist, numberOfTrips, planeName, intmax);
    delete[] planeName; 
  } // determineBestPlane()
} // determineBestPlane() 

void displayPlaneInformation(const Plane *planes, int *tracker)
{
  cout << "\nPlane Information\n";
  cout << left << setw(12) << "Name";
  cout << left << setw(6) << "Pass.";
  cout << left << setw(6) << "Range";
  cout << left << setw(6) << "Speed";
  cout << left << setw(7) << "Fuel";
  cout << left << setw(6) << "MPG";
  cout << left << setw(6) << "$/mi";
  cout << left << setw(12) << "Price * 10^6\n";

  for (int i = 0; i < *tracker; i++)
  {
    cout << planes[i];
  } // displaying all planes' information

  return;
} // displayPlaneInformation()

void readPlane(Plane *planes, int *tracker)
{
  ifstream fp;
  fp.open("planes.dat", ios::binary);
  int i = 0;
  
  while(fp.read((char*)&planes[i], sizeof(Plane)))
    i++;

  *tracker = i;
} // readPlane()

void determineAirportTraffic(const Vector *cities)
{
  char airport[80];
  int index;
  cout << "\nPlease enter an airport abbreviation (XXX): ";
  cin >> airport;
  index = cities->findAirport(airport);

  if (index >= 0 && index >= 0)
    cities->calcAirportTraffic(index);
}  // determinAirportTraffic()


int getChoice()
{
  int choice;

  do
  {
    cout << "\nFlight Simulator Menu\n";
    cout << "0. Done.\n";
    cout << "1. Determine distance and passengers between two airports.\n";
    cout << "2. Determine all traffic from one airport.\n";
    cout << "3. Display planes information.\n";
    cout << "4. Add plane information.\n";
    cout << "5. Determine best plane between two airports.\n\n";
    cout << "Your choice (0 - 5): ";
    cin >> choice;
    cin.ignore(1000, '\n');
   
    if  (choice < 0 || choice > 5)
      cout << "Your choice must be between 0 and 5. Please try again.\n";
  } while(choice < 0 || choice > 5);
   
  return choice;
}  // getChoice()  


void run(const Vector *cities, Plane *planes, int *tracker)
{
  int choice;
  
//  for(index1 = 0; index1 < cities->count; index1++)
//    for(index2 = index1 + 1; index2  < cities->count; index2++)
//      calcDistance(cities, index1, index2);

  do
  {
    choice = getChoice();
    
    if (choice == 1)
    {
      int ppl = 0;
      int dist = 0;
      int opt = 1;
      
      calcDistance(cities, &ppl, &dist, &opt);
    } // calling calcDistance()
    else  // Done or determine traffic
      if (choice == 2)
        determineAirportTraffic(cities);
    else // display the plane information 
      if (choice == 3)
        displayPlaneInformation(planes, tracker);
    else // add plane information
      if (choice == 4)
        addPlaneInformation(planes, tracker);
    else // determine the best plane
      if (choice == 5)
        determineBestPlane(planes, tracker, cities);
  } while(choice != 0);
}  // run())


int main(int argc, char** argv) 
{
  Plane planes[10];
  int tracker = 0;
  readPlane(planes, &tracker);

  Vector cities;
  cities.readCities();
  cities.readAirports();
  cities.cleanCities();
//  srand(1);
//  for(int i = 0; i < cities.count; i++)
//    cout << "1\n" << cities.cityArray[i].airport << ' ' << cities.cityArray[rand() % cities.count].airport << endl;
//  printf("%s %s %lf %lf\n", cities.cityArray[i].name, cities.cityArray[i].airport, cities.cityArray[i].latitude, cities.cityArray[i].longitude);
  run(&cities, planes, &tracker);
  return 0;
} // main())