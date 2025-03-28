#include "region.h"

//-------------------------------------------------------------------------
Region::Region()
: m_selected( false )
, m_mesh( NULL )
{
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
Region::Region( vector<Point> _pts,
                vector<Curve*> _curves, vector<bool> _curveOrients )
: m_selected( false )
{
 this->m_pts = _pts;
 this->m_curves = _curves;
 this->m_curveOrients = _curveOrients;
 this->m_mesh = NULL;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
Region::~Region()
{
 if( m_mesh )
  delete m_mesh;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
Region::getBoundBox( double* _xmin, double* _xmax,
                     double* _ymin, double* _ymax )
{
 if( m_pts.size() < 1 )
  return;

 *_xmin = *_xmax = m_pts[0].getX();
 *_ymin = *_ymax = m_pts[0].getY();

 if( m_pts.size() == 1 )
  return;

 for (int j = 1; j < m_pts.size(); j++)
 {
  if( m_pts[j].getX() < *_xmin) *_xmin = m_pts[j].getX();
  if( m_pts[j].getX() > *_xmax) *_xmax = m_pts[j].getX();
  if( m_pts[j].getY() < *_ymin) *_ymin = m_pts[j].getY();
  if( m_pts[j].getY() > *_ymax) *_ymax = m_pts[j].getY();
 }
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<vector<int>> 
Region::getCurveSdvs(  )
{
 vector<vector<int>> loops;
 vector<int> loop;
 for (int i = 0; i < m_curves.size(); i++)
 {
  int nCurveSdv = m_curves[i]->getNumberOfSubdiv();
  loop.push_back( nCurveSdv );
 }
 loops.push_back( loop );
 return loops;
}

//-------------------------------------------------------------------------
vector<Point> 
Region::getCurveSdvPts()
{
 vector<Point> bound;
 for (int i = 0; i < m_curves.size(); i++)
 {
  vector<Point> curvePts = m_curves[i]->getSubdivPoints();
  if( m_curveOrients[i] )
  {
   for (int j = 0; j < curvePts.size()-1; j++)
   {
    bound.push_back(curvePts[j]);
   }
  }
  else
  {
   for (int j = curvePts.size()-1; j > 0 ; j--)
   {
    bound.push_back(curvePts[j]);
   }
  }
 }

 return bound;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
Region::delMesh()
{
 if( m_mesh != NULL )
 {
  delete m_mesh;
  m_mesh = NULL;
 }
}
//-------------------------------------------------------------------------
