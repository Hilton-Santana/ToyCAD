#ifndef CURVE_H
#define CURVE_H

// includes
//----------
#include "point.h"

// STL C++
#include <vector>
using namespace std;


/*!
* CLASS
* Curve
*
* Base class to define the curves geometric objects. 
*
*/
class Curve
{
 public:
  enum CurveType{ LINE, POLYLINE, QUADBEZIER, CUBICBEZIER, CIRCLE, CIRCLEARC };
  Curve();
  virtual ~Curve();
  virtual int getType() = 0;
  virtual void addPoint( double _x, double _y ) = 0;
  virtual Point getPoint( double _t ) = 0;
  virtual bool isPossible() = 0;
  virtual bool isUnlimited() = 0;
  virtual vector<Point> getPoints() = 0;
  virtual vector<Point> getPointsToDraw() = 0;
  virtual vector<Point> getPointsToDraw( Point _pt ) = 0;
  virtual double closestPoint( double* _x, double* _y ) = 0;
  virtual void getBoundBox( double* _xmin, double* _xmax,
                            double* _ymin, double* _ymax ) = 0;
  virtual double getXinit() = 0;
  virtual double getYinit() = 0;
  virtual double getXend() = 0;
  virtual double getYend() = 0;
  int getNumberOfPoints() { return m_nPts; };
  void setNumberOfSubdiv( int _nSdv ){ m_nSdv = _nSdv; };
  int getNumberOfSubdiv() { return m_nSdv; };
  vector<Point> getSubdivPoints();
  void setSelected( bool _select ) { m_selected = _select; };
  bool isSelected() { return m_selected; };

 protected:
  int m_nPts;  // number of control points
  int m_nSdv;  // number of subdivision segments
  bool m_selected;
};

#endif // CURVE_H
