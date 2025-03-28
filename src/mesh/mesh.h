#ifndef MESH_H
#define MESH_H

#include "point.h"
#include <vector>
using namespace std;

class Mesh
{
 public:
  Mesh(vector<Point>& _pts, vector<vector<int>>& _conn);
  vector<Point> getPts(){ return m_pts; };
  vector<vector<int>> getConn(){ return m_conn; };

 protected:
  vector<Point> m_pts;
  vector<vector<int>> m_conn;
};

#endif // MESH_H
