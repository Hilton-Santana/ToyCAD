#include "line.h"

#include <math.h>

//-------------------------------------------------------------------------
Line::Line()
{
 m_nPts = 0;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
Line::Line( double _x1, double _y1, double _x2, double _y2 )
{
 m_x1 = _x1;
 m_y1 = _y1;
 m_x2 = _x2;
 m_y2 = _y2;
 m_nPts = 2;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
Line::addPoint( double _x, double _y )
{
 if( m_nPts == 0 )
 {
  m_x1 = _x;
  m_y1 = _y;
  m_nPts++;
 }
 else if( m_nPts == 1 )
 {
  m_x2 = _x;
  m_y2 = _y;
  m_nPts++;
 }
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
Point 
Line::getPoint( double _t )
{
 double vx = m_x2 - m_x1;
 double vy = m_y2 - m_y1;
 double xOn, yOn;
 if( _t < 0 )
 {
  xOn = m_x1;
  yOn = m_y1;
 }
 else if( _t > 1 )
 {
  xOn = m_x2;
  yOn = m_y2;
 }
 else
 {
  xOn = m_x1 + _t * vx;
  yOn = m_y1 + _t * vy;
 }
 return Point(xOn, yOn);
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool 
Line::isPossible()
{
 if( m_nPts < 2 )
 {
  return false;
 }
 return true;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point> 
Line::getPoints()
{
 if( m_nPts == 1 )
 {
 vector<Point> tempPts( 1 );
 tempPts[0] = Point( m_x1, m_y1 );
 return tempPts;
 }
 vector<Point> tempPts( 2 );
 tempPts[0] = Point( m_x1, m_y1 );
 tempPts[1] = Point( m_x2, m_y2 );
 return tempPts;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point> 
Line::getPointsToDraw()
{
 vector<Point> tempPts( 2 );
 tempPts[0] = Point( m_x1, m_y1 );
 tempPts[1] = Point( m_x2, m_y2 );
 return tempPts;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point> 
Line::getPointsToDraw( Point _pt )
{
 vector<Point> tempPts( 2 );
 tempPts[0] = Point( m_x1, m_y1 );
 if( m_nPts == 2 )
 {
  tempPts[1] = Point( m_x2, m_y2 );
 }
 else if( m_nPts == 1 )
 {
  tempPts[1] = _pt;
 }
 return tempPts;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
double 
Line::closestPoint( double* _x, double* _y )
{
 double vx = m_x2 - m_x1;
 double vy = m_y2 - m_y1;
 double t = (vx*(*_x-m_x1) + vy*(*_y-m_y1)) / (vx*vx + vy*vy);
 double xOn, yOn;
 if( t < 0.0 )
 {
  xOn = m_x1;
  yOn = m_y1;
 }
 else if( t > 1.0 )
 {
  xOn = m_x2;
  yOn = m_y2;
 }
 else
 {
  xOn = m_x1 + t * vx;
  yOn = m_y1 + t * vy;
 }
 double dist = sqrt((xOn-*_x)*(xOn-*_x)+(yOn-*_y)*(yOn-*_y));
 *_x = xOn;
 *_y = yOn;
 return dist;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
Line::getBoundBox( double* _xmin, double* _xmax,
                   double* _ymin, double* _ymax )
{
 *_xmin = (m_x1 < m_x2) ? m_x1 : m_x2;
 *_xmax = (m_x1 > m_x2) ? m_x1 : m_x2;
 *_ymin = (m_y1 < m_y2) ? m_y1 : m_y2;
 *_ymax = (m_y1 > m_y2) ? m_y1 : m_y2;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
Line::setPoints( double _x1, double _y1, double _x2, double _y2 )
{ 
 m_x1 = _x1; 
 m_x2 = _x2; 
 m_y1 = _y1; 
 m_y2 = _y2; 
}
//-------------------------------------------------------------------------
