#include "tesselation.h"
#include "compgeom.h"


//-------------------------------------------------------------------------
void 
Tesselation::triangleParing( vector<Point>& _p, vector<vector<int> >& _t )
{

  // triangulate(polygon *p, triangulation *t)
  size_t counter = 0;
  size_t pn = _p.size();
  int* l = new int[pn];  // left neighbor indices
  int* r = new int[pn];  // right neighbor indices
  bool* isPolyPt = new bool[pn];
  size_t i; // counter
  for( i=0; i<pn; i++ ) 
  { // initialization 
    l[i] = ((i-1) + pn) % pn;
    r[i] = ((i+1) + pn) % pn;
    isPolyPt[i] = true;
  }
  i = pn-1;
  while(_t.size() < (pn-2)) 
  {
    i = r[i];
    if (ear_Q(l[i],i,r[i],_p,isPolyPt)) 
    {
      // Original implementation (SKIENA & REVILLA, 2002):
      // add_triangle(t,l[i],i,r[i],p);
      vector<int> tri(3);
      tri[0] = l[i];
      tri[1] = i;
      tri[2] = r[i];
      _t.push_back( tri );
      isPolyPt[i] = false;
      // update left and right neighbor lists
      l[ r[i] ] = l[i];
      r[ l[i] ] = r[i];
    }
  }
  delete r;
  delete l;
  delete isPolyPt;
}
//-------------------------------------------------------------------------



//-------------------------------------------------------------------------
bool 
Tesselation::ear_Q( int _i, int _j, int _k, vector<Point>& _p, bool* _isPolyPt )
{
  vector<Point*> t(3); // coordinates for points i,j,k 
  size_t m; // counter
  // Original implementation (SKIENA & REVILLA, 2002):
  // copy_point(p->p[i],t[0]);
  // copy_point(p->p[j],t[1]);
  // copy_point(p->p[k],t[2]);
  t[0] = &_p[_i];
  t[1] = &_p[_j];
  t[2] = &_p[_k];
  // Check for angle ijk (centered in j) greater then 180 degrees 
  if( cw(t[0],t[1],t[2]) ) 
    return (false);
  for( m=0; m<_p.size(); m++ ) 
  {
   if( _isPolyPt[m] )
     if( (m!=_i) && (m!=_j) && (m!=_k) )
       if( point_in_triangle(&_p[m],t) ) 
         return (false);
  }
  return (true);
}
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
bool 
Tesselation::cw( Point* _a, Point* _b, Point* _c )
{
// Original implementation (SKIENA & REVILLA, 2002):
//  return( signed_triangle_area(_a,_b,_c) < 0 );
  return( !CompGeom::isLeftSide(_a,_b,_c) );
}
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
// Original implementation (SKIENA & REVILLA, 2002) (not used):
double
Tesselation::signed_triangle_area( Point* _a, Point* _b, Point* _c )
{
  return( ( _a->getX()*_b->getY() - _a->getY()*_b->getX()
          + _a->getY()*_c->getX() - _a->getX()*_c->getY()
          + _b->getX()*_c->getY() - _c->getX()*_b->getY()) / 2.0 );
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool 
Tesselation::point_in_triangle( Point* _p, vector<Point*>& _t )
{
  for( int i=0; i<3; i++ )
    // Original implementation (SKIENA & REVILLA, 2002):
    // if( cw(_t[i],_t[(i+1)%3],_p) ) 
    if( CompGeom::isRightSide(_t[i],_t[(i+1)%3],_p) ) 
      return( false );
  return( true );
}
//-------------------------------------------------------------------------

