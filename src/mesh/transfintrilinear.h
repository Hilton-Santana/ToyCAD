#ifndef TRANSFINTRILINEAR_H
#define TRANSFINTRILINEAR_H

#include "meshgenerator.h"

class TransfinTrilinear : public MeshGenerator
{
 public:
  TransfinTrilinear();

  // virtual methods implemented
  bool setParam( vector<vector<int>> _loops );
  bool generateMesh( vector<Point> _bound,
                     vector<Point>& _pts, vector<vector<int>>& _conn );

 private:
  int m_n;  // number of subdivisions (segments) in u, v, and w directions
};

#endif // TRANSFINTRILINEAR_H
