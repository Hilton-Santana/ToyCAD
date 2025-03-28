#ifndef TRANSFINBILINEAR_H
#define TRANSFINBILINEAR_H

#include "meshgenerator.h"

class TransfinBilinear : public MeshGenerator
{
 public:
  TransfinBilinear();

  // virtual methods implemented
  bool setParam( vector<vector<int>> _loops );
  bool generateMesh( vector<Point> _bound,
                     vector<Point>& _pts, vector<vector<int>>& _conn );
  int id_pts(int i, int j);

 private:
  int m_nu;  // number of subdivisions (segments) in u direction
  int m_nv;  // number of subdivisions (segments) in v direction 
};

#endif // TRANSFINBILINEAR_H
