#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

class Word
{ 
  string scrabWord;
  short value;

public:
  
  Word(string word, int val = 0) : scrabWord(word), value(val) {}
  bool operator < (const Word& rhs) const
  { 
    return scrabWord < rhs.scrabWord;
  } // operator <
  Word() {};
  short checkLegalWord(set <Word> &x, string& s);
  void print(set<string> &temp, string& word, unsigned max);
  void calcPermutations(set<Word> &x, string& word, string& origWord);
  void mapping(map<char, short> &x);
  //void readWords(set<Word> &words, map<char, short> &x); 
  void scrabble(set<Word> &words, char* filename);
}; // Word

short Word::checkLegalWord(const set <Word> &x, const string& s)
{
  short value = 0;
  set<Word>::iterator iter;
  iter = x.find(Word(s, value)); // CHECK value will always be 0

  if (iter != x.end())
    return (iter->value); // CHECK value is private

  else // else
    return 0;
} // checkLegalWord()

void Word::print(set<string> &temp, string& word, unsigned max)
{
  set<string>::iterator iter;
  iter = temp.begin();

  cout << setw(2) << max << " " << word << ":";

  for (iter = temp.begin(); iter != temp.end(); iter++)
    cout << " " << *iter;

  cout << "\n";
} // print()

void Word::calcPermutations(set<Word> &x, string& word, string& origWord)
{ 
  set<string> temp;
  set<Word>::iterator iter;
  unsigned i, max = 0, value;

  do
  {
    for (i = 0; i <= word.size(); i++)
    {
      string s = word.substr(0, i);
      value = checkLegalWord(x, s); // iter = x.find(

      if ((value == max) != 0)
        temp.insert(s);

      else // else
      if (value > max) 
      {
        max = value;
        
        if (!temp.empty())
          temp.erase(temp.begin(), temp.end());

        temp.insert(s);
      } // word with higher value
    } // checking all substrings
  } while (next_permutation(word.begin(), word.end()));
 
  if (max == 0)
    cout << setw(2) << "0" << " " << origWord << ": " << "No words found.\n";

  else // else
    print(temp, origWord, max);
} // calcPermutations()

void Word::mapping(map<char, short> &x)
{ 
  int c, i;
  short values[26] = { 1, 3, 3, 2, 1, 4, 2, 4, 2, 8, 5, 1, 3, 1, 1, 3, 10,
                       1, 1, 1, 1, 4, 4, 8, 4, 10 };
  
  for (i = 0, c = 97; c < 123 && i < 26; c++, i++)
    x.insert(pair<char, short> (c, values[i]));
} // mapping()

void readWords(set<Word> &words, map<char, short> &x)
{ 
  string word, line;
  ifstream inf;
  inf.open("words.txt");
  
  while (getline(inf, line) && !line.empty())
  { 
    short result = 0;
    string::iterator iter;

    size_t found = line.find_first_not_of("abcdefghijklmnopqrstuvwxyz ");
    
    if (found == string::npos && line.size() <= 7)
    {
      for (iter = line.begin(); iter != line.end(); iter++)
        result += x.find(*iter)->second;

      words.insert(Word(line, result));
    } // finding value of word and storing it in set
  } // Till end of file is reached

  inf.close();
} // readWords()

void Word::scrabble(set<Word> &words, char* filename)
{
  string word, line;
  ifstream inf;
  inf.open(filename);
  //int tmp = 0;
  while (getline(inf, line))
  { 
    //if(tmp==0) tmp++;
    //else cout << endl;
    istringstream record(line);
    record >> word;

    if (word.size() != 7)
      cout << setw(2) << "0" << " " << word << ":" << " No words found.\n";

    else // else
    {
      string origWord(word);
      sort(word.begin(), word.end());
      calcPermutations(words, word, origWord);
    } // sort the string and calc permutations
  } // Till end of file is reached
} // scrabble()

int main(int argc, char** argv)
{
  set<Word> words;
  map<char, short> letterValue;
  Word temp;
  
  temp.mapping(letterValue);
  readWords(words, letterValue);
  temp.scrabble(words, *(argv + 1));
} // main()
