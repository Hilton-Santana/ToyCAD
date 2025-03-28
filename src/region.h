#ifndef REGION_H
#define REGION_H

#include <vector>
using namespace std;

#include "point.h"
#include "curves/curve.h"
#include "mesh/mesh.h"

class Region
{
 public:
  Region();
  Region( vector<Point> _pts,
          vector<Curve*> _curves, vector<bool> _curveOrients );
  ~Region();
  vector<Point> getPoints(){ return m_pts; };
  vector<Curve*> getCurves(){ return m_curves; };
  vector<bool> getCurveOrients(){ return m_curveOrients; };
  void setSelected( bool _select ) { m_selected = _select; };
  bool isSelected() { return m_selected; };
  void getBoundBox( double* _xmin, double* _xmax,
                    double* _ymin, double* _ymax );
  vector<vector<int>> getCurveSdvs();
  vector<Point> getCurveSdvPts();
  void setMesh( Mesh* _mesh ){ m_mesh = _mesh; };
  void delMesh();
  Mesh* getMesh(){ return m_mesh; };

 private:
  vector<Point> m_pts;          // boundary points
  vector<Curve*> m_curves;      // vector of region curves
  vector<bool> m_curveOrients;  // orientations of curves with respect to
                                //      counter-clockwise region boundary
  bool m_selected;
  Mesh* m_mesh;
};

#endif // REGION_H
