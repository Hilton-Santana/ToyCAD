#ifndef DELAUNAY_H
#define DELAUNAY_H

#include "meshgenerator.h"

class Delaunay : public MeshGenerator
{
 public:
  Delaunay();

  // virtual methods implemented
  bool setParam( vector<vector<int>> _loops );
  bool generateMesh( vector<Point> _bound,
                     vector<Point>& _pts, vector<vector<int>>& _conn );

 private:
  vector<vector<int>> m_loops;    // number of points in each loop

};

#endif // DELAUNAY_H
