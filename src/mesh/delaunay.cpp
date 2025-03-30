
#include "delaunay.h"
#include <math.h>
#include <string>
#include <sstream>

#include "triangle.h"


//-------------------------------------------------------------------------
Delaunay::Delaunay()
{
 m_loops.clear();
}
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
bool
Delaunay::setParam( vector<vector<int>> _loops )
{
  if( _loops.size() < 1 )
    return false;

  m_loops = _loops;

  return true;
}
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
bool 
Delaunay::generateMesh( vector<Point> _bound,
                        vector<Point>& _pts,
                        vector<vector<int> >& _conn )
{
  // Get number of loops (number of connected portions of boundary)
  int nLoops = (int)m_loops.size();

  // Get number of holes (inside loops) in the region
  int nHole = nLoops - 1;

  // Assume that exterior boundary is the first loop of given array and
  // get number of points in exterior boundary.
  int np = 0;
  for( unsigned int i = 0; i < (int)m_loops[0].size(); i++ )
    np += m_loops[0][i];

  // If there is at least one hole, get points of each hole
  // and one point inside each hole
  vector<vector<Point>> holes;
  vector<Point> hole;
  vector<Point> insideHoles;
  int nHolePts = 0;
  int hole_offset = np;
  if( nHole > 0 )
  {
    Point insideHole;
    for( unsigned int ih = 0; ih < nHole; ih++ )
    {
      hole.clear();
      insideHole.setCoords(0.0,0.0);
      unsigned int nph = 0; // number of hole points
      for( unsigned int i = 0; i < (int)m_loops[ih+1].size(); i++ )
        nph += m_loops[ih+1][i];
      nHolePts += nph;
      for( unsigned int i = hole_offset; i < hole_offset+nph; ++i )
      {
        insideHole += _bound[i];
        hole.push_back( _bound[i] );
      }
      holes.push_back( hole );
      insideHole = insideHole / (double)nph;
      insideHoles.push_back( insideHole );
      hole_offset += nph;
    }
  }

  // get boundary
  struct triangulateio in, out, vorout;

  // points and segments
  in.numberofpoints = np + nHolePts;
  in.pointlist = new double[in.numberofpoints * 2];
  in.numberofsegments = np + nHolePts;
  in.segmentlist = new int[in.numberofsegments * 2];
  in.segmentmarkerlist = NULL;

  // stores the holes info, if there is any hole
  hole_offset = 0;
  if( nHole > 0 )
  {
    for( unsigned int ih = 0; ih < holes.size(); ++ih )
    {
      unsigned int nph = holes[ih].size();
      int indexH = 0;
      for( unsigned int i = hole_offset; i < hole_offset+nph; ++i )
      {
        in.pointlist[i*2]   = holes[ih][indexH].getX();
        in.pointlist[i*2+1] = holes[ih][indexH].getY();
        in.segmentlist[i*2+0] = i;
        in.segmentlist[i*2+1] = i+1;
        indexH++;
      }
      in.segmentlist[(hole_offset+nph)*2-1] = hole_offset;
      hole_offset += nph;
    }
  }

  // stores the boundary points and segments data
  double maxL = euclidiandistance( _bound[1], _bound[0] );
  double minL = maxL;
  int indexB = 0;
  for( int i = hole_offset; i < hole_offset+np; ++i )
  {
    in.pointlist[i*2]   = _bound[indexB].getX();
    in.pointlist[i*2+1] = _bound[indexB].getY();
    in.segmentlist[i*2+0] = i;
    in.segmentlist[i*2+1] = i+1;
    indexB++;
    double dist2p = euclidiandistance( _bound[indexB-1], _bound[(indexB)%np] );
    if( minL > dist2p )
      minL = dist2p;
    if( maxL < dist2p )
      maxL = dist2p;
  }
  in.segmentlist[(np+nHolePts)*2-1] = hole_offset;

  in.numberofpointattributes = 0;
  in.pointattributelist      = (REAL *)NULL;
  in.pointmarkerlist         = (int *)NULL;
  in.numberofholes           = nHole;
  in.holelist                = new double[in.numberofholes * 2];
  if( nHole > 0 )
  {
    for( unsigned int ih = 0; ih < holes.size(); ++ih )
    {
      in.holelist[ih*2]   = insideHoles[ih].getX();
      in.holelist[ih*2+1] = insideHoles[ih].getY();
    }
  }

  in.numberofregions         = 0;
  in.regionlist              = (REAL *)NULL;

  out.pointlist = (REAL *) NULL;             //Not needed if -N switch used. 
  out.pointattributelist = (REAL *) NULL;
  out.pointmarkerlist = (int *) NULL; // Not needed if -N or -B switch used. 
  out.trianglelist = (int *) NULL;          // Not needed if -E switch used. 
  out.triangleattributelist = (REAL *) NULL;
  out.neighborlist = (int *) NULL;         // Needed only if -n switch used. 
  out.segmentlist = (int *) NULL;
  out.segmentmarkerlist = (int *) NULL;
  out.edgelist = (int *) NULL;             // Needed only if -e switch used. 
  out.edgemarkerlist = (int *) NULL;   // Needed if -e used and -B not used. 

  double size = (maxL+minL)/2.0;
  double maxArea = maxL*maxL*sqrt(3.0)/4.0; // equilateral triangle area
  std::ostringstream sstream;
  sstream << maxArea;
  std::string varAsString1 = sstream.str();
  std::string varAsString2 = "pzq30a"+varAsString1+"YiCV";

  // Delaunay Triangulation
  //triangulate();
  triangulate((char *)varAsString2.c_str(), &in, &out, &vorout);

  // checks 
  // get number of points and triangles
  if( out.numberofpoints == 0 || out.numberoftriangles == 0 )
    return false;

  // get points
  for( int i = 0; i < out.numberofpoints; ++i )
  {
    Point tmp( out.pointlist[i*2+0], out.pointlist[i*2+1] );
    _pts.push_back( tmp );
  }

  // get connectivity
  for( int i = 0; i < out.numberoftriangles; ++i )
  {
    vector<int> triang;
    triang.push_back( out.trianglelist[i*3+0] );
    triang.push_back( out.trianglelist[i*3+1] );
    triang.push_back( out.trianglelist[i*3+2] );
    _conn.push_back( triang );
  }

  /* trifree() is just a wrapper for free() */
  trifree(out.pointlist);
  trifree(out.pointmarkerlist);
  trifree(out.edgelist);
  trifree(out.edgemarkerlist);
  trifree(out.trianglelist);
  trifree(out.triangleattributelist);
  trifree(out.segmentlist);
  trifree(out.segmentmarkerlist);

  return true;
}

