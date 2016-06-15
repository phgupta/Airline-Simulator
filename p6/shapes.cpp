#include <iostream> 
using namespace std;

class Shape
{
  friend  ostream& operator << (ostream& os, const Shape &shape);
  virtual void write(ostream& os) const = 0;
}; // Shape class

ostream& operator << (ostream& os, const Shape &shape)
{
 shape.write(os);
 return os;
} // operator << ()

class IntersectingLines : public Shape
{
  void write(ostream& os) const; 
}; // IntersectingLines class

void IntersectingLines::write(ostream& os) const
{
  os << "    /\\" << endl;
  os << "   /  \\" << endl;
  os << "  /    \\" << endl;
  os << " /      \\" << endl;
  os << "/        \\" << endl;
} // IntersectingLines()

class BaseLine : public Shape
{
  void write(ostream& os) const;
}; // BaseLine class

void BaseLine::write(ostream& os) const
{
  os << "----------" << endl; 
} // BaseLine()

class ParallelLines : public Shape
{
  void write(ostream& os) const;
}; // ParallelLines class

void ParallelLines::write(ostream& os) const
{
  os << "|        |" << endl;
  os << "|        |" << endl;
  os << "|        |" << endl;
} // ParallelLines()

class BlankLines : public Shape
{
  void write(ostream& os) const;
}; // BlankLines class

void BlankLines::write(ostream& os) const
{
  os << "\n\n";
} // BlankLines()

class Circle : public Shape
{
  void write(ostream& os) const;
}; // Circle class

void Circle::write(ostream& os) const
{
  os << "    *" << endl;
  os << "  *   *" << endl;
  os << "   * *" << endl;
} // Circle()

int main()
{
  Shape* shapes[9];
  shapes[0] = new IntersectingLines;
  shapes[1] = new BaseLine;
  shapes[2] = new ParallelLines;
  shapes[3] = new BaseLine;
  shapes[4] = new BlankLines;
  shapes[5] = new Circle;
  shapes[6] = new IntersectingLines;
  shapes[7] = new BaseLine;
  shapes[8] = new IntersectingLines;

  for (int i = 0; i < 9; i++)
  {
    cout << *shapes[i];
  } // output

  return 0;

  //delete [] shapes;
} // main()
