#ifndef CITYLIST_H
#define CITYLIST_H

#include "city.h"

class CityNode 
{
  friend class CityList;
  City city;
  CityNode* next;
  
  public: 
    CityNode(City c, CityNode* n); 
}; // CityNode class

class CityList
{
  private:

    static int count;
    CityNode* head;
    CityNode* tail;

  public:
    CityList(); 
    ~CityList(); 
    static int getCount(); 
    CityList& operator+= (const City& rhs);
    CityList& operator-= (const City& rhs); 
    City& operator[](int index); 
    const City& operator[](int index) const; 
}; // CityList class

#endif
