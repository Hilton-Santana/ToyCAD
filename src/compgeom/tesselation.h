#ifndef TESSELATION_H
#define TESSELATION_H

#include <vector>
using namespace std;
#include "point.h"


class Tesselation
{

public:  

  /**
   * @brief Constructs a triangulation/tessellation for a non-convex hull given by
   *        a set of points [SKIENA & REVILLA, 2002. Programming Challenges, p.319]
   * @param _p is the set of points of the non-convex hull
   * @param _t is the triangulation of the region
   */
  static void triangleParing( vector<Point>& _p, vector<vector<int> >& _t );


private:

  // creates a ear for the hull
  static bool ear_Q( int _i, int _j, int _k, vector<Point>& _p, bool* _isPolyPt );
  // verifies if the order of the triangle connectivity
  static bool cw( Point* _a, Point* _b, Point* _c );
  // computes the area of a triangle keeping the sign of orientation
  static double signed_triangle_area( Point* _a, Point* _b, Point* _c );
  // verifies if the point _p is inside the triangle _t
  static bool point_in_triangle( Point* _p, vector<Point*>& _t );


};


#endif // TESSELATION_H
