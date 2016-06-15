#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
using namespace std;

void readLimeric(char** filename, vector<string> &text)
{
  string line;
  ifstream inf;
  inf.open(filename[1]);
  
  while (getline(inf, line))
    text.push_back(line);
  
  inf.close();
} // readLimeric()

void writeResult(char** filename, vector<string> &text)
{
  ofstream of;
  of.open(filename[3]);
  
  vector<string>::iterator iter;
  
  for (iter = text.begin(); iter != text.end(); iter++)
    of << *iter << endl;
  
  of.close();
} // writeResult()

void insert(vector<string> &text, istringstream& record)
{
  string word, line;
  int lineNo, pos;
  record >> lineNo;
  record >> pos;

  while (record >> word)
  {
    line.append(word);

    if (pos != 10)
      line.append(" ");
  } // while loop

  vector<string>::iterator iter;
  iter = text.begin();
  iter += lineNo;
  *iter = iter->insert(pos, line);
} // insert()

void replace(vector<string> &text, istringstream& record)
{
  string word, line;
  int lineNo, spos, epos;
  record >> lineNo >> spos >> epos;
  
  while (record >> word)
  {
    line.append(word);
    line.append(" ");
    
    if (record >> word)
    {
      line.append(word);
    }  // end if
  }  // end while
  
  vector<string>::iterator iter;
  iter = text.begin();
  iter += lineNo;
  
  *iter = iter->replace(spos, epos - spos, line);
} // replace()

void find(vector<string> &text, istringstream& record)
{
  string word, pos;
  record >> word;
  
  vector<string>::iterator iter;
  
  for (iter = text.begin(); iter != text.end(); iter++)
  {
    size_t found = iter->find(word);

    if (found != string::npos)
    {
      ostringstream ss;
      int lineNo = iter - text.begin();
      ss << lineNo;
      string position = ss.str();
      pos.append(" ");
      pos.append(position);
    } // if match is found
  } // traversing through the vector
  
  cout << word << pos << " \n";
} // find()

void deleteL(vector<string> &text, istringstream& record)
{
  int spos, epos;
  record >> spos;
  record >> epos;
  
  text.erase(text.begin() + spos, text.begin() + epos + 1);
} // deleteL()

void erase(vector<string> &text, istringstream& record)
{
  string word, line; int i = -1, j = -1;
  vector<string>::iterator iter;

  record >> word; line.append(word);
  
  while (record >> word)
  {
    ++j;
    line.append(" ");
    line.append(word);
  } // appending the words to be replaced 

  if (j == -1)
    line.append(" ");
  
  for (iter = text.begin(); iter != text.end(); iter++)
  {
    if (iter->compare(line) == 0)
      i = iter - text.begin();
    
    else // else
    {
      size_t found = iter->find(line);

      if (found != string::npos) 
        iter->erase(iter->find(line), line.size());
    } // if it matches a word 
  } // traversing through the vector
  
  if (i != -1)
    text.erase(text.begin() + i, text.begin() + (i + 1));

  return;
} // erase()

void copy(vector<string> &text, istringstream& record)
{
  int startLine, endLine, destLine;
  record >> startLine;
  record >> endLine;
  record >> destLine;
  
  vector<string>::iterator iter;
  vector<string> temp;
  
  for (iter = text.begin() + startLine; iter != text.begin() + endLine + 1;
       iter++)
  {
    string str(*iter);
    temp.push_back(str);
  } // copying the specified lines to temp
  
  text.insert(text.begin() + destLine, temp.begin(), temp.end());
} // copy()

void move(vector<string> &text, istringstream& record)
{
  int startLine, endLine, destLine;
  record >> startLine;
  record >> endLine;
  record >> destLine;
  
  vector<string>::iterator iter;
  vector<string> temp;
  
  for (iter = text.begin() + startLine; iter != text.begin() + endLine + 1;
       iter++)
  {
    string str(*iter);
    temp.push_back(str);
  } // copying the specified lines to temp
  
  text.insert(text.begin() + destLine, temp.begin(), temp.end());

  if (destLine > startLine)
    text.erase(text.begin() + startLine, text.begin() + endLine + 1);

  else // else
    text.erase(text.begin() + startLine + endLine,
               text.begin() + startLine + endLine + (endLine - startLine) + 1);
} // move()

int main(int argc, char** argv)
{
  vector<string> text;
  readLimeric(argv, text);
  
  string line, word;
  ifstream inf;
  inf.open(argv[2]);
  
  while (getline(inf, line) && !line.empty())
  {
    istringstream record(line);
    record >> word;

    string::iterator iter;
    int value;

    for (iter = word.begin(); iter != word.begin() + 1; iter++)
    {
      value = *iter;  
    } // parsing word

    switch (value)
    {
      case 'I' : insert(text, record);
                 break;
      case 'R' : replace(text, record);
                 break;
      case 'F' : find(text, record);
                 break;
      case 'D' : deleteL(text, record);
                 break;
      case 'E' : erase(text, record);
                 break;
      case 'C' : copy(text, record);
                 break;
      case 'M' : move(text, record);
                 break;
    } // switch statement
  } // reading command file
  
  writeResult(argv, text);
  
  inf.close();
  return (0);
} // main()
