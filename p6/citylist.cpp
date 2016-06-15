// Author: Sean Davis
#include <iostream>
#include <cstdlib>
#include "citylist.h"
using namespace std;

int CityList::count = 0;

CityNode::CityNode(const City &c, CityNode *node) : city(c), next(node)
{
  
}  // CityNode())

CityList::CityList() : head(NULL), tail(NULL) 
{
} // CityList()

CityList::~CityList() 
{
  for (CityNode *ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  }  // for each node
} // ~CityList()


int CityList::getCount()
{
  return count;
}  // getCount()

CityList&  CityList::operator += (const City &rhs)
{
  if (tail)
    tail = tail->next = new CityNode(rhs, NULL);
  else // an empty list
    head = tail = new CityNode(rhs, NULL);
  
  count++;
  return *this;
}  // operator+=


CityList& CityList::operator -= (const City &rhs)
{
  CityNode *ptr, *prev = NULL;
  
  for (ptr = head; ptr && ! (ptr->city == rhs); ptr = ptr->next)
    prev = ptr;
  
  if (ptr)
  {
    count--;
    
    if (!prev)  // found at front of list
    {
      head = ptr->next;
      
      if (!head)  // head == NULL so now empty list
        tail = NULL;
    }  // if removing first node
    else // removing node after the first
    {
      prev->next = ptr->next;
      
      if (tail == ptr)
        tail = prev;
    }  // else removing after the first node
    
    delete ptr;
  }  // if found 

  return *this;
}  // operator -=


const City& CityList::operator [] (int index) const
{
  int pos = 0;
  CityNode *ptr;
  
  for (ptr = head; ptr && pos != index; ptr = ptr->next, pos++);
   
  if (!ptr)
  {
     cout << "Error in array indexing!\n";
     exit(1);
  }  // if index beyond end of list

  return ptr->city; 
}  // const operator[]
 
 
City& CityList::operator [] (int index)
{
  int pos = 0;
  CityNode *ptr;
   
  for (ptr = head; ptr && pos != index; ptr = ptr->next, pos++);
   
  if (!ptr)
  {
    cout << "Error in array indexing!\n";
    exit(1);
  } // if index beyond end of the array.

  return ptr->city; 
}  // non-const operator[]
