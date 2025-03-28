#ifndef _MESHGENERATOR
#define _MESHGENERATOR


#include "point.h"
#include <vector>
using namespace std;

class MeshGenerator
{
 public:
  enum
  {
    TRANSFIN_BILINEAR,
    TRANSFIN_TRILINEAR, 
    DELAUNAY,
    ADVANCEDFRONT
  };
  virtual bool setParam( vector<vector<int>> _loops ) = 0;
  virtual bool generateMesh( vector<Point> _bound,
                             vector<Point>& _pts, vector<vector<int>>& _conn ) = 0;
 private:
};

#endif
