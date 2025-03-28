#ifndef COMPGEOM_H
#define COMPGEOM_H

#include "point.h"

class CompGeom
{
 public:
  enum SIGN {
    NEGATIVE = -1,
    ZERO = 0,
    POSITIVE = 1
  };

  enum IntersectionType {
    DO_NOT_INTERSECT,
    DO_INTERSECT,
    TOUCH,
    COLLINEAR,
    PARALLEL /* not used */
  };

  enum SEGPOS { // Classification of a point w.r.t. segment
    BEFORE_SEG,   // Outside and before segment
    START_SEG,    // At start point of segment
    INSIDE_SEG,   // Inside segment
    END_SEG,      // At end point of segment
    AFTER_SEG     // Outside and after segment
  };

  // Return the sign (NEGATIVE, ZERO, or POSITIVE) of the oriented
  // twice area formed by three given points.
  // This function uses a predicate for robustly performing the
  // orientation tests define by Jonathan Richard Shewchuk in
  // "Adaptive Precision Floating- Point Arithmetic and Fast Robust
  // Geometric Predicates."  Technical Report CMU-CS-96-140,
  // School of Computer Science, Carnegie Mellon,
  // University, Pittsburgh, Pennsylvania, May 1996.
  static SIGN signOrient2d( Point* _p1, Point* _p2, Point* _p3 );

  // Return the signed value of the oriented twice area formed by
  // three given points.
  // This function uses a predicate for robustly performing the
  // orientation tests define by Jonathan Richard Shewchuk.
  static double valOrient2d( Point* _p1, Point* _p2, Point* _p3 );

  // Return a flag (true or false) stating whether the three given
  // points are collinear.
  // This function uses a predicate for robustly performing the
  // orientation tests define by Jonathan Richard Shewchuk.
  static bool areCollinear( Point* _p1, Point* _p2, Point* _p3 ){
    return signOrient2d(_p1,_p2,_p3) == ZERO;
  };

  // Return a flag (true or false) stating whether the third given
  // point is on the left side of oriented segment formed by the
  // first given points.
  // This function uses a predicate for robustly performing the
  // orientation tests define by Jonathan Richard Shewchuk.
  static bool isLeftSide( Point* _p1, Point* _p2, Point* _p3 ){
    return signOrient2d(_p1,_p2,_p3) == POSITIVE;
  };

  // Return a flag (true or false) stating whether the third given
  // point is on the right side of oriented segment formed by the
  // first given points.
  // This function uses a predicate for robustly performing the
  // orientation tests define by Jonathan Richard Shewchuk.
  static bool isRightSide( Point* _p1, Point* _p2, Point* _p3 ){
    return signOrient2d(_p1,_p2,_p3) == NEGATIVE;
  };

  // Return the sign (NEGATIVE, ZERO, or POSITIVE) of the oriented
  // twice area formed by three given points.
  // This function uses conventional floating-point operations to 
  // compute the area and compares the area result with a hard-coded
  // very small tolerance value (ABSTOL).
  static SIGN signArea2d( Point* _p1, Point* _p2, Point* _p3 );

  // Return the signed value of the oriented twice area formed by
  // three given points.
  // This function uses conventional floating-point operations to 
  // compute the signed area.
  static double valArea2d( Point* _p1, Point* _p2, Point* _p3 );

  // Get closest point on line 'p1'-'p2'.
  // Returns the distance between given point and closest point.
  // Also returns parametric value (from -infinity to +infinity)
  // of closest point along the line.
  static double getClosestPointLine( Point* _p1, Point* _p2, Point* _p,
                                     Point* _pC, double* _t );

  // Get closest point on line segment 'p1'-'p2'.
  // Returns the distance between given point and closest point.
  // Also returns parametric value (between 0 and 1) of closest point
  // along the line.
  // The difference between this function and function 'getClosestPointLine'
  // is that a closest point outside the limits of segment 'p1-p2' is 
  // snapped to one of the segment end points.
  static double getClosestPointSegment( Point* _p1, Point* _p2, Point* _p,
                                        Point* _pC, double* _t );

  // Check for collinear segments 'p1'-'p2' and 'p3'-'p4'.
  static bool checkCollinearSegments( Point* _p1, Point* _p2,
                                      Point* _p3, Point* _p4 );

  // Checks for two line segments intersection:
  // Checks whether segment 'p1'-'p2' intercepts segment 'p3'-'p4'.
  // Returns an integer intersection type value.
  // In case there is intersection, outputs the result in 'pi' parameter
  // and returns parametric values ('t12' and 't34' between 0 and 1) along
  // the two segments.
  // Ref.:
  // M. Gavrilova & J.G. Rokne - Reliable line segment intersection testing,
  // Computer-Aided Design, Vol. 32, Issue 12, pp. 737–745, 2000.
  static int computeSegmentSegmentIntersection( Point* _p1, Point* _p2,
                                                Point* _p3, Point* _p4,
                                                Point* _pi,
                                                double* _t12, double* _t34 );

  // This function classifies the projection of a given 'p' point w.r.t. a
  // given segment 'p1-p2'.
  // It returns the classified position of the projection of a point
  // along the infinite line that contains a given segment.
  // It also returns the parametric value of the project point along segment.
  // Its main used is to classify the points of two collinear segments,
  // but it may be used to classify points projected at the infinite line
  // that contains a segment.

  static SEGPOS getPtPosWrtSegment( Point* _p1, Point* _p2, Point* _p,
                                    double* _t );

  // This function returns a flag indicating whether the vertices
  // of a polygon are in counter-clockwise order.
  // The algorithm is as follows:
  // Traverse the loop of coordinates, assuming that it is in counter-
  // clockwise order, computing the components of the "area" of the
  // enclosed polygon.  The total "area" components are computed by
  // adding "area" components (cross product components) of
  // triangles sides formed by the first, previous, and current
  // vertices.  If the loop is not convex, some of the triangle
  // areas might be negative, but those will be compensated by other
  // positive triangle areas so that the final area is positive.
  // (area here is actually twice the area).
  // (positive here means in the direction of the face normal).
  static bool isCounterClockwisePolygon( vector<Point>& _poly );

  // This function returns a flag indicating whether the given point 'p'
  // is inside a polygon 'poly'.
  // The algorithm counts the number of intersections that a horizontal
  // line emanating at the point 'p' in positive x direction makes with
  // the boundary lines of the polygon. If the number of intersections
  // is odd, the point is inside de polygon. Otherwise, it is outside
  // the polygon.
  // If ray passes at an horizontal segment on polygon boundary, do not
  // count any intersection.
  // If ray passes at a vertex of the polygon, only consider intersection
  // if boundary segment is above ray.
  static bool isPointInPolygon( vector<Point>& _poly, Point* _p );

 private:
  static double ABSTOL;       // Absolute tolerance value.

};

#endif // COMPGEOM_H
