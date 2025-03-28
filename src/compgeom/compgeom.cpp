#include <math.h>
#include "compgeom.h"

#ifndef ABS
#define ABS(x) (((x) < 0)? -(x): (x))
#endif

#define ORIENT2D_ADAPTIVE
#undef  ORIENT2D_NONROBUST
#undef  ORIENT2D_EXACT
#undef  ORIENT2D_EXACTSLOW

double CompGeom::ABSTOL = 1e-7;

// Predicates Header Files
extern "C" 
{
#include "predicates.h"
}

//-------------------------------------------------------------------------
CompGeom::SIGN
CompGeom::signOrient2d( Point* _p1, Point* _p2, Point* _p3 )
{
 double det = 0.0;

 // to start Shewchuk predicates
 exactinit();
 double pa[2] = {_p1->getX(),_p1->getY()};
 double pb[2] = {_p2->getX(),_p2->getY()};
 double pc[2] = {_p3->getX(),_p3->getY()};

 // we test here several different implementations
#ifdef ORIENT2D_ADAPTIVE
 det = orient2d( pa, pb, pc );
#endif
#ifdef ORIENT2D_EXACT
 det = orient2dexact( pa, pb, pc );
#endif
#ifdef ORIENT2D_EXACTSLOW
 det = orient2dslow( pa, pb, pc );
#endif
#ifdef ORIENT2D_NONROBUST
 det = orient2dfast( pa, pb, pc );
#endif
 if( det != 0.0 )
 {
  if( det > 0.0 )
   return POSITIVE;
  else
   return NEGATIVE;
 } 
 return ZERO;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
double
CompGeom::valOrient2d( Point* _p1, Point* _p2, Point* _p3 )
{
 double det = 0.0;

 // to start Shewchuk predicates
 exactinit();
 double pa[2] = {_p1->getX(),_p1->getY()};
 double pb[2] = {_p2->getX(),_p2->getY()};
 double pc[2] = {_p3->getX(),_p3->getY()};

 // we use the exact implementation to get orient2d value
 det = orient2dexact( pa, pb, pc );

 return det;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
CompGeom::SIGN
CompGeom::signArea2d( Point* _p1, Point* _p2, Point* _p3 )
{
 double det = area2d(*_p1, *_p2, *_p3);
 if( ABS(det) < ABSTOL )
  return ZERO;
 if( det > 0.0 )
  return POSITIVE;
 return NEGATIVE;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
double
CompGeom::valArea2d( Point* _p1, Point* _p2, Point* _p3 )
{
 return area2d(*_p1, *_p2, *_p3);
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
double 
CompGeom::getClosestPointLine( Point* _p1, Point* _p2, Point* _p,
                               Point* _pC, double* _t )
{
 Point v12 = *_p2 - *_p1;
 Point v1p = *_p  - *_p1;

 *_t = dotprod( v12, v1p ) / sizesquare(v12);
 *_pC = *_p1 + *_t * v12;

 double dist = size(*_p - *_pC);
 return dist;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
double 
CompGeom::getClosestPointSegment( Point* _p1, Point* _p2, Point* _p,
                                  Point* _pC, double* _t )
{
 Point v12 = *_p2 - *_p1;
 Point v1p = *_p  - *_p1;

 *_t = dotprod( v12, v1p ) / sizesquare(v12);

 if( ABS(*_t) < ABSTOL )
 {
  *_pC = *_p1;
  *_t = 0.0;
 }
 else if( ABS(*_t-1.0) < ABSTOL )
 {
  *_pC = *_p2;
  *_t = 1.0;
 }
 else
 {
  *_pC = *_p1 + *_t * v12;
 }

 double dist = size(*_p - *_pC);
 return dist;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool 
CompGeom::checkCollinearSegments( Point* _p1, Point* _p2,
                                  Point* _p3, Point* _p4 )
{
// Get signs of oriented twice area for points p1-p2-p3 and for points p1-p2-p4
 CompGeom::SIGN sign123 = signArea2d(_p1,_p2,_p3);
 CompGeom::SIGN sign124 = signArea2d(_p1,_p2,_p4);

// Check for collinear segments
 if( (sign123 == CompGeom::ZERO) && (sign124 == CompGeom::ZERO) )
 {
  return true;
 }
 return false;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
int 
CompGeom::computeSegmentSegmentIntersection( Point* _p1, Point* _p2,
                                             Point* _p3, Point* _p4,
                                             Point* _pi,
                                             double* _t12, double* _t34 )
{
 double area123 = 0.0; // twice the area of triangle 123
 double area124 = 0.0; // twice the area of triangle 124
 double area341 = 0.0; // twice the area of triangle 341
 double area342 = 0.0; // twice the area of triangle 342

 // Discard intersection if second segment is located to the left (_l) or 
 // to the right (_r) of horizontal bounding box limits of first segment.
 double x12_l, x12_r;
 double x34_l, x34_r;
 x12_l = (_p1->getX() < _p2->getX()) ? _p1->getX() : _p2->getX();
 x12_r = (_p1->getX() > _p2->getX()) ? _p1->getX() : _p2->getX();
 x34_l = (_p3->getX() < _p4->getX()) ? _p3->getX() : _p4->getX();
 x34_r = (_p3->getX() > _p4->getX()) ? _p3->getX() : _p4->getX();
 if( (x12_r+ABSTOL) < x34_l || x34_r < (x12_l-ABSTOL) )
 {
  return DO_NOT_INTERSECT;
 }

 // Discard intersection if second segment is located below 
 // bottom (_b) or above top (_t) of bounding box of first segment.
 double y12_b, y12_t;
 double y34_b, y34_t;
 y12_b = (_p1->getY() < _p2->getY()) ? _p1->getY() : _p2->getY();
 y12_t = (_p1->getY() > _p2->getY()) ? _p1->getY() : _p2->getY();
 y34_b = (_p3->getY() < _p4->getY()) ? _p3->getY() : _p4->getY();
 y34_t = (_p3->getY() > _p4->getY()) ? _p3->getY() : _p4->getY();
 if( (y12_t+ABSTOL) < y34_b || y34_t < (y12_b-ABSTOL) )
 {
  return DO_NOT_INTERSECT;
 }

// Get signs of oriented twice area for points p1-p2-p3 and for points p1-p2-p4
 CompGeom::SIGN sign123 = signArea2d(_p1,_p2,_p3);
 CompGeom::SIGN sign124 = signArea2d(_p1,_p2,_p4);

 // Check for collinear segments
 /*** COMPLETE HERE - COMPGEOM: 01 ***/
 if (checkCollinearSegments(_p1, _p2, _p3, _p4))
 {
	 return DO_NOT_INTERSECT;
 }
 /*** COMPLETE HERE - COMPGEOM: 01 ***/

 // Check for second segment on the same side of first segment
 /*** COMPLETE HERE - COMPGEOM: 02 ***/
 if (sign123 == POSITIVE && sign124 == POSITIVE)
 {
	 return DO_NOT_INTERSECT;
 }
 else if (sign123 == NEGATIVE && sign124 == NEGATIVE)
 {
	 return DO_NOT_INTERSECT;
 }

 /*** COMPLETE HERE - COMPGEOM: 02 ***/

 // Get signs of oriented twice area for points p3-p4-p1 and for points p3-p4-p2
 CompGeom::SIGN sign341 = signArea2d(_p3, _p4, _p1);
 CompGeom::SIGN sign342 = signArea2d(_p3, _p4, _p2);

 // Check for first segment on the same side of second segment
 /*** COMPLETE HERE - COMPGEOM: 03 ***/
 if (sign341 == POSITIVE && sign342 == POSITIVE)
 {
	 return DO_NOT_INTERSECT;
 }
 else if (sign341 == NEGATIVE && sign342 == NEGATIVE)
 {
	 return DO_NOT_INTERSECT;
 }

 /*** COMPLETE HERE - COMPGEOM: 03 ***/

 // Check for one point of second segment touching first segment.
 // Also compute the intersection point and the parametric values
 // ('t12' and 't34' between 0 and 1) along the two segments.
 // In this case, 't34' is either equal to 0 or equal to 1.
 /*** COMPLETE HERE - COMPGEOM: 04 ***/
 if (sign123 == ZERO && (sign124 == NEGATIVE || sign124 == POSITIVE))
 {
	 Point* pTemp;
	 double distTemp;
	 *_pi = *_p3;
	 *_t34 = 0;
	 distTemp = getClosestPointSegment(_p1, _p2, _pi, pTemp, _t12);
	 return DO_INTERSECT;
 }
 else if (sign124 == ZERO && (sign123 == NEGATIVE || sign123 == POSITIVE))
 {
	 Point* pTemp;
	 double distTemp;
	 *_pi = *_p4;
	 *_t34 = 1;
	 distTemp = getClosestPointSegment(_p1, _p2, _pi, pTemp, _t12);
	 return DO_INTERSECT;
 }

 /*** COMPLETE HERE - COMPGEOM: 04 ***/

 // Check for one point of first segment touching second segment
 // Also compute the intersection point and the parametric values
 // ('t12' and 't34' between 0 and 1) along the two segments.
 // In this case, 't12' is either equal to 0 or equal to 1.
 /*** COMPLETE HERE - COMPGEOM: 05 ***/

 if (sign341 == ZERO && (sign342 == NEGATIVE || sign342 == POSITIVE))
 {
	 Point* pTemp;
	 double distTemp;
	 *_pi = *_p1;
	 *_t12 = 0;
	 distTemp = getClosestPointSegment(_p3, _p4, _pi, pTemp, _t34);
	 return DO_INTERSECT;
 }
 else if (sign342 == ZERO && (sign341 == NEGATIVE || sign341 == POSITIVE))
 {
	 Point* pTemp;
	 double distTemp;
	 *_pi = *_p2;
	 *_t12 = 1;
	 distTemp = getClosestPointSegment(_p3, _p4, _pi, pTemp, _t34);
	 return DO_INTERSECT;
 }
 /*** COMPLETE HERE - COMPGEOM: 05 ***/

 // When get to this point, there is an intersection point of the
 // two segments. Compute parametric values of intersection point
 // along each segment.
 /*** COMPLETE HERE - COMPGEOM: 06 ***/
 area123 = valArea2d(_p1, _p2, _p3);
 area124 = valArea2d(_p1, _p2, _p4);
 *_t34 = area123 / (area123 - area124);
 area341 = valArea2d(_p3, _p4, _p1);
 area342 = valArea2d(_p3, _p4, _p2);
 *_t12 = area341 / (area341 - area342);
 /*** COMPLETE HERE - COMPGEOM: 06 ***/

// Compute intersection point (there are two equivalent options)
// Point v12 = *_p2 - *_p1;
// *_pi = *_p1 + *_t12 * v12;
 Point v34 = *_p4 - *_p3;
 *_pi = *_p3 + *_t34 * v34;
 return DO_INTERSECT;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
CompGeom::SEGPOS 
CompGeom::getPtPosWrtSegment( Point* _p1, Point* _p2, Point* _p, double* _t )
{
 Point v12 = *_p2 - *_p1;
 Point v1p = *_p  - *_p1;

 // Get parametric value of project point on segment line
 *_t = dotprod( v12, v1p ) / sizesquare(v12);

 if( ABS(*_t) < ABSTOL )
 {
  return START_SEG;
 }
 else if( ABS(*_t-1.0) < ABSTOL )
 {
  return END_SEG;
 }
 else if( *_t < 0.0 )
 {
  return BEFORE_SEG;
 }
 else if( *_t > 1.0 )
 {
  return AFTER_SEG;
 }

 return INSIDE_SEG;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool 
CompGeom::isCounterClockwisePolygon( vector<Point>& _poly )
{
 double area = 0.0; // twice the enclosed polygon area

 // Compute area assuming that polygon is in counter-clockwise order
 for( unsigned int i = 2; i < _poly.size(); i++ ) 
 {
  area += area2d( _poly[0], _poly[i-1], _poly[i] );
 }

 // If area is greater than zero, then polygon is in counter-clockwise 
 // order, otherwise it is in clockwise order.
 if( area > 0.0 )
  return true;
 return false;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool 
CompGeom::isPointInPolygon( vector<Point>& _poly, Point* _p )
{
 double  x = _p->getX();
 double  y = _p->getY();
 int     n = _poly.size();               // number of polygon points
 int     ni = 0;                         // number of intersections

 for( int i = 0; i < n; i++ )
 {
  Point p1 = _poly[i];                   // first point of current line segment
  Point p2 = _poly[(i+1)%n];             // second point of current line segment
/*** COMPLETE HERE - COMPGEOM: 07 ***/
  CompGeom::SIGN sign12p = signArea2d(&p1, &p2, _p);
  // teste de aresta horizontal
  if (p1.getY() == p2.getY())
	  continue;
  // teste se o ponto está abaixo da aresta
  if (p1.getY() > y && p2.getY() > y)
	  continue;
  // teste se o ponto está acima da aresta
  if (p1.getY() < y && p2.getY() < y)
	  continue;
  // teste se o ponto está a esquerda da aresta
  if ((y > p1.getY() && sign12p == NEGATIVE) || (y < p1.getY() && sign12p == POSITIVE))
	  continue;
  // testa interseção no ponto superior
  if (p2.getY() == y)
	  continue;
  ni++;
/*** COMPLETE HERE - COMPGEOM: 07 ***/
 }

 // If number of intersections is odd, point is inside polygon.
 if( (ni % 2) > 0 )
  return true;

 // If number of intersections if even, point is outside polygon.
 return false;
}
//-------------------------------------------------------------------------
