#ifndef CURVECOLLECTOR_H
#define CURVECOLLECTOR_H

#include "curves/curve.h"

class CurveCollector
{
 public:
  CurveCollector();
  virtual ~CurveCollector();

  void setCurveType( int _type );
  int getCurveType() { return m_curveType; };
  void startCurveCollection();
  Curve* getCollectedCurve() const { return m_curve; };
  void endCurveCollection();
  bool isActive();
  bool isCollecting();
  bool hasFinished();
  bool isUnlimited();
  int insertPoint( double _x, double _y, double _tol );
  int addTempPoint( double _x, double _y );
  vector<Point> getDrawPoints();
  vector<Point> getPoints();
  void getBoundBox( double* _xmin, double* _xmax,
                    double* _ymin, double* _ymax );
  void reset();
  void kill();

 private:
  int m_curveType;
  Curve *m_curve;
  Point m_prevPt;
  Point m_tempPt;
};

#endif // CURVECOLLECTOR_H
