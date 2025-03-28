#ifndef MYMODEL_H
#define MYMODEL_H

#include <vector>
using namespace std;

#include "point.h"
#include "color.h"
#include "curves/curve.h"
#include "region.h"

class MyModel
{
 public:
  MyModel();
  ~MyModel();
  bool isEmpty() { return (m_curves.size() < 1); };
  vector<Curve*> getCurves() { return m_curves; };
  vector<Region*> getRegions() { return m_regions; };
  void getBoundBox(double* _xmin, double* _xmax,
                   double* _ymin, double* _ymax);
  void selectPick( double _x, double _y, double _tol, bool _shiftkey );
  void selectFence( double _xmin, double _xmax,
                    double _ymin, double _ymax, bool _shiftkey );
  void insertCurve( Curve* _curve );
  void delCurve( int _curveId );
  void delAllCurves();
  void delSelectedCurves();
  void delRegion( int _regionId );
  void delAllRegions();
  void delSelectedRegions();
  bool snapToCurve( double* _x, double* _y, double _tol );
  bool intersectTwoSelectedCurves();
  void createRegion();
  void setNumSubdivOfSelectedCurves( int _nSdv );
  bool getNumSubdivOfFirstSelectedCurve( int* _nSdv );
  void generateMeshSelectedRegions( int _meshGenerationType );

 protected:
  vector<Curve*> m_curves;
  vector<Region*> m_regions;
};

#endif // MYMODEL_H
