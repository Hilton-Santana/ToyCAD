#ifndef POINT_H
#define POINT_H

#include <vector>
using namespace std;
#include <iostream>
#include <math.h>

class Point
{
 friend inline bool   equal      (Point& p1, Point& p2, Point& tol);
 friend inline bool   operator== (Point& p1, Point& p2);
 friend inline bool   operator!= (Point& p1, Point& p2);
 friend inline Point  operator+  (Point p1, Point p2);
 friend inline Point& operator+= (Point& p1, Point& p2);
 friend inline Point  operator-  (Point p1, Point p2);
 friend inline Point& operator-= (Point& p1, Point& p2);
 friend inline Point  operator*  (Point p,  double s);
 friend inline Point  operator*  (double s,  Point p);
 friend inline Point  operator/  (Point p,  double s);
 friend inline double euclidiandistance (Point& p1, Point& p2);
 friend inline double manhattandistance (Point& p1, Point& p2);
 friend inline double sizesquare (Point& p);
 friend inline double size       (Point p);
 friend inline double dotprod    (Point p1, Point p2);
 friend inline double crossprod  (Point p1, Point p2);
 friend inline Point  normalize  (Point p);
 friend inline double area2d     (Point& p1, Point& p2, Point& p3 );
 friend inline std::ostream& operator<< (std::ostream& cout, Point& p);

 public:
  Point();
  Point( double _cX, double _cY );
  Point( vector<double> _coords );
  vector<double> getCoords();
  double getX() { return m_x; };
  double getY() { return m_y; };
  void setCoords( double _cX, double _cY ) { m_x = _cX; m_y = _cY; };

 private:
  double m_x;
  double m_y;
};

///@name PointUtilities
//@{
/// Equality test with tolerance (Manhattan distance).
inline
bool equal (Point& p1, Point& p2, Point& tol)
{
 return fabs(p1.m_x-p2.m_x)<tol.m_x &&
        fabs(p1.m_y-p2.m_y)<tol.m_y;
}

/// Equality test without tolerance.
inline
bool operator== (Point& p1, Point& p2)
{
 return (p1.m_x == p2.m_x) && (p1.m_y == p2.m_y);
}

/// Inequality test without tolerance.
inline
bool operator!= (Point& p1, Point& p2)
{
 return !(p1==p2);
}

/// Addition.
inline
Point operator+ (Point p1, Point p2)
{
 return Point(p1.m_x+p2.m_x, p1.m_y+p2.m_y);
}
/// Addition.
inline
Point& operator+= (Point& p1, Point& p2)
{
 p1 = p1+p2;
 return p1;
}

/// Subtraction.
inline
Point operator- (Point p1, Point p2)
{
 return Point(p1.m_x-p2.m_x,p1.m_y-p2.m_y);
}
/// Subtraction.
inline
Point& operator-= (Point& p1, Point& p2)
{
 p1 = p1-p2;
 return p1;
}

/// Scalar multiplication.
inline
Point operator* (Point p, double s)
{
 return Point(p.m_x*s,p.m_y*s);
}
/// Scalar multiplication.
inline
Point operator* (double s, Point p)
{
 return Point(p.m_x*s,p.m_y*s);
}

/// Division by scalar.
inline
Point operator/ (Point p, double s)
{
 if( s == 0.0 )
  return Point(0.0,0.0);
 return Point(p.m_x/s,p.m_y/s);
}

/// Euclidian distance.
inline
double euclidiandistance (Point& p1, Point& p2)
{
 return sqrt((p1.m_x-p2.m_x)*(p1.m_x-p2.m_x)+
             (p1.m_y-p2.m_y)*(p1.m_y-p2.m_y));
}

/// Manhattan distance.
inline
double manhattandistance (Point& p1, Point& p2)
{
 return fabs(p1.m_x-p2.m_x) + fabs(p1.m_y-p2.m_y);
}

/// Square of size (vector).
inline
double sizesquare (Point& p)
{
 return (p.m_x*p.m_x + p.m_y*p.m_y);
}

/// Size (vector).
inline
double size (Point p)
{
 return sqrt(sizesquare(p));
}

/// Dot product (vector).
inline
double dotprod (Point p1, Point p2)
{
 return p1.m_x*p2.m_x + p1.m_y*p2.m_y;
}

/// Cross product (vector).
inline
double crossprod (Point p1, Point p2)
{
 return p1.m_x*p2.m_y - p2.m_x*p1.m_y;
}

/// Normalize (vector).
inline
Point normalize(Point p)
{
 double norm = size(p);
 if( norm == 0.0 )
  return Point(0.0,0.0);
 return Point(p.m_x/norm, p.m_y/norm);
}

/// Twice the signed area of triangle p1-p2-p3
inline
double area2d (Point& p1, Point& p2, Point& p3 )
{
 Point A = p2 - p1;
 Point B = p3 - p1;
 return crossprod(A,B);
}

/// Output.
inline
std::ostream& operator<< (std::ostream& cout, Point& p)
{
 cout << "(" << p.m_x << "," << p.m_y << ")";
 return cout;
}
//@}

#endif // POINT_H
