#ifndef CITYLIST_H
  #define	CITYLIST_H

#include "city.h"

class CityList;

class CityNode
{
  City city;
  CityNode *next;
  CityNode(const City &c, CityNode *node);
  friend class CityList;
};  // class CityNode


class CityList 
{
  CityNode *head;
  CityNode *tail;
  static int count;
public:
  CityList();
  CityList(const CityList& orig);
  ~CityList();
  static int getCount();
 CityList&  operator += (const City &rhs);
 CityList& operator -= (const City &rhs);
 const City& operator [] (int index) const;
 City& operator [] (int index);

}; // class CityList 

#endif	// CITYLIST_H 

