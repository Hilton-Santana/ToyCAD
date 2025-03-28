
#include "transfintrilinear.h"
#include <math.h>

// Macro definition for indexing a triangular matrix with size = m_n+1
// stored in a vector
#define id_pts(i,j) ((((i)*(2*m_n-(i)+3))/2)+(j))

//-------------------------------------------------------------------------
TransfinTrilinear::TransfinTrilinear()
: m_n( 0 )
{
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool 
TransfinTrilinear::setParam( vector<vector<int>> _loops )
{
 // Check for just one loop
 if( _loops.size() != 1 )
  return false;

 // Check for exactly three curves on loop
 vector<int> curveSbdvs = _loops[0];
 if( curveSbdvs.size() != 3 )
   return false;

 // Check for equal number of subdivisions on all curves of loop
 if( curveSbdvs[0] != curveSbdvs[1] )
  return false;
 if( curveSbdvs[0] != curveSbdvs[2] )
  return false;

 // Save parameter of valid boundary loop
 m_n = curveSbdvs[0];

 return true;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool 
TransfinTrilinear::generateMesh( vector<Point> _bound,
                                 vector<Point>& _pts, vector<vector<int> >& _conn  )
{
 // Total number of boundary nodes must be consistent with
 // number of boundary segments
 if( _bound.size() != (m_n)*3)
  return false;

 int id_bound = 0;
 Point pt(0.0,0.0);
 int i;
 int j;

 // Allocate point vector in row major order int k = 0;
 for( i = 0; i <= m_n; i++ )
 {
  for( j = 0; j <= m_n-i; j++ )
  {
   _pts.push_back( pt );
  }
 }

 // Input nodes from first boundary curve
 i = 0;
 for( j = 0; j < m_n; j++ )
 {
  _pts[id_pts(i,j)] = _bound[id_bound];
  id_bound++;
 }

 // Input node from second boundary curve
 for( i = 0; i < m_n; i++ )
 {
  j = m_n - i;
  /*** COMPLETE HERE - TRANSFINTRILINEAR: 01 ***/
  _pts[id_pts(i, j)] = _bound[id_bound];
  id_bound++;
  /*** COMPLETE HERE - TRANSFINTRILINEAR: 01 ***/
 }

 // Input node from third boundary curve
 /*** COMPLETE HERE - TRANSFINTRILINEAR: 02 ***/
 j = 0;
 for (i = m_n; i > 0; i--)
 {
	 /*** COMPLETE HERE - TRANSFINTRILINEAR: 01 ***/
	 _pts[id_pts(i, j)] = _bound[id_bound];
	 id_bound++;
	 /*** COMPLETE HERE - TRANSFINTRILINEAR: 01 ***/
 }
 /*** COMPLETE HERE - TRANSFINTRILINEAR: 02 ***/

 // Generate interior nodes
 for( i = 1; i < m_n; i++ )
 {
  for( j = 1; j < m_n-i; j++ )
  {
   _pts[id_pts(i,j)] = (_pts[id_pts(i,    m_n-i)] * j/(m_n-i) +
                        _pts[id_pts(i,    0    )] * (m_n-i-j)/(m_n-i) +
                        _pts[id_pts(i+j,  0    )] * i/(i+j) +
                        _pts[id_pts(0,    i+j  )] * j/(i+j) +
                        _pts[id_pts(0,    j    )] * (m_n-i-j)/(m_n-j) +
                        _pts[id_pts(m_n-j,j    )] * i/(m_n-j) -
                        _pts[id_pts(0,    0    )] * (m_n-i-j)/(m_n) -
                        _pts[id_pts(0,    m_n  )] * j/m_n -
                        _pts[id_pts(m_n,  0    )] * i/m_n) * 0.5;
  }
 }

 // Generate quadrilateral elements
 int node1, node2, node3;
 vector<int> tria;
 for( i = 0; i < m_n; i++ )
 {
  for( j = 0; j < m_n-i; j++ )
  {
   /*** COMPLETE HERE - TRANSFINTRILINEAR: 03 ***/
	  if (j > 0)
	  {
		  node1 = id_pts(i, j);
		  node2 = id_pts(i + 1, j);
		  node3 = id_pts(i + 1, j - 1);
		  tria.push_back(node1);
		  tria.push_back(node2);
		  tria.push_back(node3);
		  _conn.push_back(tria);
		  tria.clear();
	  }
	  node1 = id_pts(i, j);
	  node2 = id_pts(i, j + 1);
	  node3 = id_pts(i + 1, j);
	  tria.push_back(node1);
	  tria.push_back(node2);
	  tria.push_back(node3);
	  _conn.push_back(tria);
	  tria.clear();

   /*** COMPLETE HERE - TRANSFINTRILINEAR: 03 ***/
  }

 }

 return true;
}
//-------------------------------------------------------------------------
