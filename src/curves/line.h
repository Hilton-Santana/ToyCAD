#ifndef LINE_H
#define LINE_H

#include "curve.h"

class Line : public Curve
{
 public:
  Line();
  Line( double _x1, double _y1, double _x2, double _y2 );

  // virtual methods implemented
  int getType() { return (int)Curve::LINE; };
  bool isUnlimited() { return false; };
  void addPoint( double _x, double _y );
  Point getPoint( double _t );
  bool isPossible();
  vector<Point> getPoints();
  vector<Point> getPointsToDraw();
  vector<Point> getPointsToDraw( Point _pt );
  double closestPoint( double* _x, double* _y );
  void getBoundBox( double* _xmin, double* _xmax,
                    double* _ymin, double* _ymax );
  double getXinit() { return m_x1; };
  double getYinit() { return m_y1; };
  double getXend() { return m_x2; };
  double getYend() { return m_y2; };

  // specific line methods
  void setPoints( double _x1, double _y1, double _x2, double _y2 );

 private:
  double m_x1;
  double m_y1;
  double m_x2;
  double m_y2;
};

#endif // LINE_H
