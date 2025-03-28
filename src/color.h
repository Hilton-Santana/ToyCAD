#ifndef COLOR_H
#define COLOR_H

#include <vector>
using namespace std;
#include <iostream>
#include <math.h>

class Color
{
 friend inline bool operator== (Color& c1, Color& c2);
 friend inline bool operator!= (Color& c1, Color& c2);
 friend inline std::ostream& operator<< (std::ostream& cout, Color& p);

 public:
  Color();
  Color( double _r, double _g, double _b );
  Color( vector<double> _rgb );
  vector<double> getRGB();
  double getR() { return m_r; };
  double getG() { return m_g; };
  double getB() { return m_b; };
  void setRGB( double _r, double _g, double _b )
             { m_r = _r; m_g = _g; m_b = _b; };

 private:
  double m_r;
  double m_g;
  double m_b;
};

///@name ColorUtilities
//@{

/// Equality test.
inline
bool operator== (Color& c1, Color& c2)
{
 return (c1.m_r == c2.m_r) && (c1.m_g == c2.m_g) && (c1.m_b == c2.m_b);
}

/// Inequality test.
inline
bool operator!= (Color& c1, Color& c2)
{
 return !(c1==c2);
}

/// Output.
inline
std::ostream& operator<< (std::ostream& cout, Color& p)
{
 cout << "(" << p.m_r << "," << p.m_g << "," << p.m_b << ")";
 return cout;
}
//@}

#endif // COLOR_H
