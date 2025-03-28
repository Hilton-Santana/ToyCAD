#include "mesh.h"
 
 
//-------------------------------------------------------------------------
Mesh::Mesh( vector<Point>& _pts, vector<vector<int>>& _conn )
{
 // Create mesh copying given points and connectivity arrays
 for( int i = 0; i < _pts.size(); i++ )
 {
  Point pt = _pts[i];
  m_pts.push_back( pt );
 }

 for( int i = 0; i < _conn.size(); i++ )
 {
  vector<int> _elem = _conn[i];
  vector<int> elem;
  for( int j = 0; j < _elem.size(); j++ )
  {
   int node = _elem[j];
   elem.push_back( node );
  }
  m_conn.push_back( elem );
 }
}
//-------------------------------------------------------------------------
