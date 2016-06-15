#include <iostream>
#include "citylist.h"

using namespace std; 

int CityList::count = 0; 
CityList::CityList()
{
  head = NULL;
  tail = NULL;
} // CityList constructor

CityNode::CityNode(City c, CityNode *n)
{
  city =  c;
  next = n;
} // CityNode constructor

CityList::~CityList()
{
  CityNode *ptr; 

  for (ptr = head; ptr; ptr = head) 
  {
    head = ptr -> next; 
    delete ptr; 
  } //moves head and deletes the pointer
} // Citylist destructor

int CityList::getCount()
{
  return count;
} // getCount()

CityList& CityList::operator+= (const City& rhs)
{
  CityNode* ptr = new CityNode(rhs, NULL); 

  if (head) 
  {
    tail->next = ptr; 
    tail = ptr; 
  } //checks if head exits 

  else //if head or tail does not exist 
  { 
    head = tail = ptr; 
  }// appends Node and moves tail 
  
  count++; 
  return *this; 
} // operator +=


CityList& CityList::operator-= (const City& rhs)
{
  CityNode* prev = NULL;
  CityNode* ptr;
  
  for (ptr = head; ptr && !(ptr->city == rhs); ptr = ptr->next) 
      prev = ptr; 
  
  if (ptr) 
  {
    
    if (!prev)
    {
      head = ptr->next; 
      
      if (head == NULL) 
        tail = NULL;
    } //if ptr is  NULL

    else //else  
    {
      prev->next = ptr->next; 
      
      if (ptr == tail) 
        tail = prev; 

    } //if ptr exists

    delete ptr; 
    count--;
  } //if head exists
  
  return *this; 
} // operator -=

City& CityList::operator[] (int index) 
{
  CityNode* ptr = head; 

  int counter = 0; 

  for (counter = 0; ptr && counter < index; counter++) 
  {
    ptr = ptr->next; 
  } // moves pointer

  return ptr->city;
} // operator[]

const City& CityList::operator[] (int index) const
{
  CityNode* ptr = head; 

  int counter = 0; 

  for (counter = 0; ptr && counter < index; counter++) 
  {
    ptr = ptr->next; 
  } // moves pointer

  return ptr->city;
} // const operator[]
