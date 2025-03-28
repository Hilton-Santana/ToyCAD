#ifndef GRID_H
#define GRID_H

class Grid
{
 public:
  Grid();
  void reset();
  void setSnapData( bool _isSnapOn, double _dx, double _dy );
  bool getSnapInfo();
  void getGridSpace( double* _dx, double* _dy );
  void snapTo( double* _x, double* _y );

 protected:
  // Grid data and methods
  bool m_isSnapOn;
  double m_gridX;
  double m_gridY;
};

#endif // GRID_H
