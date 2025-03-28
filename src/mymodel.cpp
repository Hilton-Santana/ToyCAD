#include <QMessageBox>
#include <math.h>

#include "mymodel.h"
#include "compgeom/compgeom.h"
#include "mesh/transfinbilinear.h"
#include "mesh/transfintrilinear.h"
#include "mesh/delaunay.h"

#include "curves/line.h"

#ifndef ABS
#define ABS(x) (((x) < 0)? -(x): (x))
#endif

#define ABSTOL (1e-7)

//--------------------------------------------------------------------
MyModel::MyModel()
{
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
MyModel::~MyModel()
{
 delAllCurves();
 delAllRegions();
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
MyModel::getBoundBox(double* _xmin, double* _xmax,
                     double* _ymin, double* _ymax)
{
 if( m_curves.size() < 1 )
 {
  *_xmin =  0.0;
  *_xmax = 10.0;
  *_ymin =  0.0;
  *_ymax = 10.0;
  return;
 }

 m_curves[0]->getBoundBox(_xmin, _xmax, _ymin, _ymax);
 for(int i = 1; i < m_curves.size(); i++)
 {
  double xmin_c, xmax_c, ymin_c, ymax_c;
  m_curves[i]->getBoundBox(&xmin_c, &xmax_c, &ymin_c, &ymax_c);
  if(xmin_c < *_xmin)
   *_xmin = xmin_c;
  if(xmax_c > *_xmax)
   *_xmax = xmax_c;
  if(ymin_c < *_ymin)
   *_ymin = ymin_c;
  if(ymax_c > *_ymax)
   *_ymax = ymax_c;
 }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
MyModel::selectPick( double _x, double _y, double _tol, bool _shiftkey )
{
 if( m_curves.size() < 1 )
  return;

 double xC, yC;
 int id_target = -1;
 double dmin = _tol;
 for(int i = 0; i < m_curves.size(); i++)
 {
  // Compute distance between given point and curve and
  // update minimum distance
  xC = _x;
  yC = _y;
  double d = m_curves[i]->closestPoint( &xC, &yC );
  if(d < dmin)
  {
   dmin = d;
   id_target = i;
  }
 }

 // Revert selection of picked curve
 if(id_target > -1)
 {
  if( m_curves[id_target]->isSelected() )
  {
   m_curves[id_target]->setSelected(false);
  } 
  else
  {
   m_curves[id_target]->setSelected(true);
  }
 }

 if( !_shiftkey )
 {
  // If shift key is not pressed, unselect all curves except 
  // the picked one (if there was one selected)
  for(int i = 0; i < m_curves.size(); i++)
  {
   if( i != id_target )
    m_curves[i]->setSelected(false);
  }
 }

 // Check whether point is inside a region.
 Point p(_x,_y);
 for(int i = 0; i < m_regions.size(); i++)
 {
  vector<Point> pts = m_regions[i]->getPoints();
  if( CompGeom::isPointInPolygon( pts, &p ) )
  {
   if( m_regions[i]->isSelected() )
    m_regions[i]->setSelected(false);
   else
    m_regions[i]->setSelected(true);
  }
  else
  {
   if( !_shiftkey )
    m_regions[i]->setSelected(false);
  }
 }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
MyModel::selectFence( double _xmin, double _xmax,
                      double _ymin, double _ymax, bool _shiftkey )
{
 if( m_curves.size() < 1 )
  return;

 bool inFence;
 double xmin_c, xmax_c, ymin_c, ymax_c;
 for(int i = 0; i < m_curves.size(); i++)
 {
  m_curves[i]->getBoundBox(&xmin_c, &xmax_c, &ymin_c, &ymax_c);
  if( (xmin_c < _xmin) || (xmax_c > _xmax) ||
      (ymin_c < _ymin) || (ymax_c > _ymax) )
   inFence = false;
  else
   inFence = true;

  if( inFence )
  {
   // Select curve inside fence
   m_curves[i]->setSelected(true);
  }
  else
  {
  // If shift key is not pressed, unselect curve outside fence
   if( !_shiftkey )
    m_curves[i]->setSelected(false);
  }
 }

 double xmin_r, xmax_r, ymin_r, ymax_r;
 for(int i = 0; i < m_regions.size(); i++)
 {
  m_regions[i]->getBoundBox(&xmin_r, &xmax_r, &ymin_r, &ymax_r);
  if( (xmin_r < _xmin) || (xmax_r > _xmax) ||
      (ymin_r < _ymin) || (ymax_r > _ymax) )
   inFence = false;
  else
   inFence = true;

  if( inFence )
  {
   // Select region inside fence
   m_regions[i]->setSelected(true);
  }
  else
  {
  // If shift key is not pressed, unselect region outside fence
   if( !_shiftkey )
    m_regions[i]->setSelected(false);
  }
 }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
MyModel::insertCurve( Curve* _curve )
{
 m_curves.push_back(_curve);
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
MyModel::delCurve( int _curveId )
{
 // Update curve information of regions in response to curve deletion.
 // In case a region uses the deleted curve, also delete this region.
 bool regionRemoved;
 do
 {
  regionRemoved = false;
  for(int i = 0; i < m_regions.size(); i++)
  {
   vector<Curve*> curvesRegion = m_regions[i]->getCurves();
   for(int j = 0; j < curvesRegion.size(); j++)
   {
    if(curvesRegion[j] == m_curves[_curveId])
    {
     delRegion(i);
     regionRemoved = true;
     break;
    }
   }
   if( regionRemoved )
   {
    break;
   }
  }
 } while( regionRemoved );

 // Remove curve from model and delete it 
 delete m_curves[_curveId];
 m_curves.erase( m_curves.begin() + _curveId );
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
MyModel::delAllCurves()
{
 while(m_curves.size() > 0)
 {
  delCurve(m_curves.size() - 1);
 }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
MyModel::delSelectedCurves()
{
 bool curveRemoved;
 do
 {
  curveRemoved = false;
  for(int i = 0; i < m_curves.size(); i++)
  {
   if( m_curves[i]->isSelected() )
   {
    delCurve(i);
    curveRemoved = true;
    break;
   }
  }
 } while( curveRemoved );
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
MyModel::delRegion(int _regionId)
{
 delete m_regions[_regionId];
 m_regions.erase(m_regions.begin() + _regionId);
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
MyModel::delAllRegions()
{
 while(m_regions.size() > 0)
 {
  delRegion(m_regions.size() - 1);
 }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
MyModel::delSelectedRegions()
{
 bool regionRemoved;
 do
 {
  regionRemoved = false;
  for(int i = 0; i < m_regions.size(); i++)
  {
   if( m_regions[i]->isSelected() )
   {
    delRegion(i);
    regionRemoved = true;
    break;
   }
  }
 } while( regionRemoved );
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
bool 
MyModel::snapToCurve( double* _x, double* _y, double _tol )
{
 if(m_curves.size() < 1)
  return false;

 double xC, yC;
 double xClst = *_x;
 double yClst = *_y;
 int id_target = -1;
 double dmin = _tol;
 double d;

 for(int i = 0; i < m_curves.size(); i++)
 {
  // Check to see whether point is close (within given tolerance)
  // to one of curve vertices. If that is the case, continue to 
  // the next curve.
  xC = m_curves[i]->getXinit();
  yC = m_curves[i]->getYinit();
  if( (ABS(*_x-xC) < _tol) && (ABS(*_y-yC) < _tol) )
  {
   d = sqrt((*_x-xC)*(*_x-xC)+(*_y-yC)*(*_y-yC));
   if(d < dmin)
   {
    xClst = xC;
    yClst = yC;
    dmin = d;
    id_target = i;
   }
   continue;
  }

  xC = m_curves[i]->getXend();
  yC = m_curves[i]->getYend();
  if( (ABS(*_x-xC) < _tol) && (ABS(*_y-yC) < _tol) )
  {
   d = sqrt((*_x-xC)*(*_x-xC)+(*_y-yC)*(*_y-yC));
   if(d < dmin)
   {
    xClst = xC;
    yClst = yC;
    dmin = d;
    id_target = i;
   }
   continue;
  }

  // Compute distance between given point and curve and
  // update minimum distance
  xC = *_x;
  yC = *_y;
  d = m_curves[i]->closestPoint( &xC, &yC );
  if(d < dmin)
  {
   xClst = xC;
   yClst = yC;
   dmin = d;
   id_target = i;
  }
 }

 if( id_target < 0 )
  return false;

 // If found a closest point on a curve, return its 
 // coordinates in the given variables.
 *_x = xClst;
 *_y = yClst;
 return true;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
bool 
MyModel::intersectTwoSelectedCurves()
{
 if(m_curves.size() < 1)
  return false;

 // Check for exactly two selected lines.
 int i_target12 = -1;
 int i_target34 = -1;
 for(int i = 0; i < m_curves.size(); i++)
 {
  if( m_curves[i]->isSelected() )
  {
   if( i_target12 == -1 )
   {
    i_target12 = i;
   }
   else if ( i_target34 == -1 )
   {
    i_target34 = i;
   }
   else  // more then two selected lines
   {
    QMessageBox msgBox;
    msgBox.setText("Cannot perform curve intersection:\n"
                   "More than two curves were selected.");
    msgBox.exec();
    return false;
   }
  }
 }

 // Check for two selected lines.
 if( i_target34 == -1 )
 {
  QMessageBox msgBox;
  msgBox.setText("Cannot perform curve intersection:\n"
                 "Exactly two curves should be selected.");
  msgBox.exec();
  return false;
 }

 // Currently only intersection of line segments are treated.
 if( (m_curves[i_target12]->getType() != Curve::LINE) ||
     (m_curves[i_target34]->getType() != Curve::LINE) )
 {
  QMessageBox msgBox;
  msgBox.setText("Cannot perform curve intersection:\n"
                 "Currently only intersection of line segments are treated.");
  msgBox.exec();
  return false;
 }

 // Get lines' points.
 vector<Point> pts12 = m_curves[i_target12]->getPoints();
 vector<Point> pts34 = m_curves[i_target34]->getPoints();
 Point p1 = pts12[0];
 Point p2 = pts12[1];
 Point p3 = pts34[0];
 Point p4 = pts34[1];
 
 // Compute intersection between two lines.
 Point pi;
 double ti_12 = 0.0;
 double ti_34 = 0.0;
 int status = CompGeom::computeSegmentSegmentIntersection(
                        &p1, &p2, &p3, &p4, &pi, &ti_12, &ti_34 );
 Line* lnA = NULL;
 Line* lnB = NULL;
 Line* lnC = NULL;
 Line* lnD = NULL;
 bool deleteLine1 = false;
 bool deleteLine2 = false;
 bool createdLine = false;

 switch( status )
 {
  default:
  case CompGeom::DO_NOT_INTERSECT:
   {
    QMessageBox msgBox;
    msgBox.setText("Cannot perform line intersection:\n"
                   "The two selected lines do not intercept.");
    msgBox.exec();
   }
   break;
  case CompGeom::COLLINEAR:
   {
    double t3_12 = 0.0;
    double t4_12 = 0.0;
    CompGeom::SEGPOS pos3_12 = CompGeom::getPtPosWrtSegment( &p1, &p2, &p3, &t3_12 );
    CompGeom::SEGPOS pos4_12 = CompGeom::getPtPosWrtSegment( &p1, &p2, &p4, &t4_12 );

    if( ((pos3_12 == CompGeom::BEFORE_SEG) && (pos4_12 == CompGeom::BEFORE_SEG)) ||
        ((pos3_12 == CompGeom::AFTER_SEG)  && (pos4_12 == CompGeom::AFTER_SEG)) )
    {
     QMessageBox msgBox;
     msgBox.setText("Cannot perform line intersection:\n"
                    "The two selected lines do not intercept.");
     msgBox.exec();
    }
    else if( ((pos3_12 == CompGeom::BEFORE_SEG) && (pos4_12 == CompGeom::START_SEG))  ||
             ((pos3_12 == CompGeom::START_SEG)  && (pos4_12 == CompGeom::BEFORE_SEG)) ||
             ((pos3_12 == CompGeom::END_SEG)    && (pos4_12 == CompGeom::AFTER_SEG))  ||
             ((pos3_12 == CompGeom::AFTER_SEG)  && (pos4_12 == CompGeom::END_SEG)) )
    {
     // Segments simply touch at one end without overlapping.
     QMessageBox msgBox;
     msgBox.setText("Cannot perform line intersection:\n"
                    "The two selected lines simply touch at one end.");
     msgBox.exec();
    }
    else if( ((pos3_12 == CompGeom::START_SEG) && (pos4_12 == CompGeom::END_SEG))  ||
             ((pos3_12 == CompGeom::END_SEG)   && (pos4_12 == CompGeom::START_SEG)) )
    {
     // Segments have common end points: just delete second segment.
     QMessageBox msgBox;
     msgBox.setText("Cannot perform line intersection:\n"
                    "The two selected lines are exactly equal.\n"
                    "One line will be deleted.");
     msgBox.exec();
     deleteLine2 = true;
    }
    else if( (pos3_12 == CompGeom::BEFORE_SEG) && (pos4_12 == CompGeom::INSIDE_SEG) )
    {
     lnA = new Line( p3.getX(), p3.getY(), p1.getX(), p1.getY() );
     lnB = new Line( p1.getX(), p1.getY(), p4.getX(), p4.getY() );
     lnC = new Line( p4.getX(), p4.getY(), p2.getX(), p2.getY() );
     deleteLine1 = true;
     deleteLine2 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::INSIDE_SEG) && (pos4_12 == CompGeom::BEFORE_SEG) )
    {
     lnA = new Line( p1.getX(), p1.getY(), p4.getX(), p4.getY() );
     lnB = new Line( p1.getX(), p1.getY(), p3.getX(), p3.getY() );
     lnC = new Line( p3.getX(), p3.getY(), p2.getX(), p2.getY() );
     deleteLine1 = true;
     deleteLine2 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::BEFORE_SEG) && (pos4_12 == CompGeom::END_SEG) )
    {
     lnA = new Line( p3.getX(), p3.getY(), p1.getX(), p1.getY() );
     deleteLine2 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::END_SEG) && (pos4_12 == CompGeom::BEFORE_SEG) )
    {
     lnA = new Line( p1.getX(), p1.getY(), p4.getX(), p4.getY() );
     deleteLine2 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::START_SEG) &&  (pos4_12 == CompGeom::INSIDE_SEG) )
    {
     lnA = new Line( p4.getX(), p4.getY(), p2.getX(), p2.getY() );
     deleteLine1 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::INSIDE_SEG) &&  (pos4_12 == CompGeom::START_SEG) )
    {
     lnA = new Line( p3.getX(), p3.getY(), p2.getX(), p2.getY() );
     deleteLine1 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::INSIDE_SEG) && (pos4_12 == CompGeom::INSIDE_SEG) )
    {
     if( t3_12 < t4_12 )
     {
      lnA = new Line( p1.getX(), p1.getY(), p3.getX(), p3.getY() );
      lnB = new Line( p4.getX(), p4.getY(), p2.getX(), p2.getY() );
     }
     else
     {
      lnA = new Line( p1.getX(), p1.getY(), p4.getX(), p4.getY() );
      lnB = new Line( p3.getX(), p3.getY(), p2.getX(), p2.getY() );
     }
     deleteLine1 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::BEFORE_SEG) && (pos4_12 == CompGeom::AFTER_SEG) )
    {
     lnA = new Line( p3.getX(), p3.getY(), p1.getX(), p1.getY() );
     lnB = new Line( p2.getX(), p2.getY(), p4.getX(), p4.getY() );
     deleteLine2 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::AFTER_SEG) && (pos4_12 == CompGeom::BEFORE_SEG) )
    {
     lnA = new Line( p1.getX(), p1.getY(), p4.getX(), p4.getY() );
     lnB = new Line( p3.getX(), p3.getY(), p2.getX(), p2.getY() );
     deleteLine2 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::INSIDE_SEG) &&  (pos4_12 == CompGeom::END_SEG) )
    {
     lnA = new Line( p1.getX(), p1.getY(), p3.getX(), p3.getY() );
     deleteLine1 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::END_SEG) &&  (pos4_12 == CompGeom::INSIDE_SEG) )
    {
     lnA = new Line( p1.getX(), p1.getY(), p4.getX(), p4.getY() );
     deleteLine1 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::START_SEG) && (pos4_12 == CompGeom::AFTER_SEG) )
    {
     lnA = new Line( p2.getX(), p2.getY(), p4.getX(), p4.getY() );
     deleteLine2 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::AFTER_SEG) && (pos4_12 == CompGeom::START_SEG) )
    {
     lnA = new Line( p3.getX(), p3.getY(), p2.getX(), p2.getY() );
     deleteLine2 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::INSIDE_SEG) && (pos4_12 == CompGeom::AFTER_SEG) )
    {
     lnA = new Line( p1.getX(), p1.getY(), p3.getX(), p3.getY() );
     lnB = new Line( p3.getX(), p3.getY(), p2.getX(), p2.getY() );
     lnC = new Line( p2.getX(), p2.getY(), p4.getX(), p4.getY() );
     deleteLine1 = true;
     deleteLine2 = true;
     createdLine = true;
    }
    else if( (pos3_12 == CompGeom::AFTER_SEG) && (pos4_12 == CompGeom::INSIDE_SEG) )
    {
     lnA = new Line( p1.getX(), p1.getY(), p4.getX(), p4.getY() );
     lnB = new Line( p4.getX(), p4.getY(), p2.getX(), p2.getY() );
     lnC = new Line( p3.getX(), p3.getY(), p2.getX(), p2.getY() );
     deleteLine1 = true;
     deleteLine2 = true;
     createdLine = true;
    }
   }
   break;
  case CompGeom::DO_INTERSECT:
   lnA = new Line( p1.getX(), p1.getY(), pi.getX(), pi.getY() );
   lnB = new Line( pi.getX(), pi.getY(), p2.getX(), p2.getY() );
   lnC = new Line( p3.getX(), p3.getY(), pi.getX(), pi.getY() );
   lnD = new Line( pi.getX(), pi.getY(), p4.getX(), p4.getY() );
   deleteLine1 = true;
   deleteLine2 = true;
   createdLine = true;
   break;
  case CompGeom::TOUCH:
   if( (ti_12 > 0.0) && (ti_12 < 1.0) )
   {
    lnA = new Line( p1.getX(), p1.getY(), pi.getX(), pi.getY() );
    lnB = new Line( pi.getX(), pi.getY(), p2.getX(), p2.getY() );
    deleteLine1 = true;
    createdLine = true;
   }
   if( (ti_34 > 0.0) && (ti_34 < 1.0) )
   {
    lnC = new Line( p3.getX(), p3.getY(), pi.getX(), pi.getY() );
    lnD = new Line( pi.getX(), pi.getY(), p4.getX(), p4.getY() );
    deleteLine2 = true;
    createdLine = true;
   }
   if( !createdLine )
   {
    // Segments simply touch at one end without overlapping.
    QMessageBox msgBox;
    msgBox.setText("Cannot perform line intersection:\n"
                   "The two selected lines simply touch at one end.");
    msgBox.exec();
   }
   break;
 }

 // Check whether one or two selected lines will be deleted
 if( deleteLine1 && deleteLine2 )
 {
  delCurve(i_target12);
  i_target34 = -1;
  for(int i = 0; i < m_curves.size(); i++)
  {
   if( m_curves[i]->isSelected() )
    i_target34 = i;
  }
  if( i_target34 != -1 )
   delCurve(i_target34);
 }
 else if( deleteLine1 && !deleteLine2 )
 {
  delCurve(i_target12);
 }
 else if( !deleteLine1 && deleteLine2 )
 {
  delCurve(i_target34);
 }

 // Insert created lines (if there is one) in model
 if( lnA != NULL )
  m_curves.push_back(lnA);
 if( lnB != NULL )
  m_curves.push_back(lnB);
 if( lnC != NULL )
  m_curves.push_back(lnC);
 if( lnD != NULL )
  m_curves.push_back(lnD);

 if( createdLine )
  return true;
 return false;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
MyModel::createRegion()
{
 vector <int> curveRegion;
 vector <bool> curveOrientation;
 list <int> selInd;
 int masterID = -1;
 int num_sel_curves;

 // Get all selected curves.
 for (int  i = 0; i<m_curves.size();i++)
 {
  if (m_curves[i]->isSelected())
  {
   if (masterID == -1)
   {
    // The master curve of region is the first curve found selected.
    masterID = i;
   }
   else
   {
    // Save all selected curves, except the master one in a list.
    selInd.push_back(i);
   }
  }
 }

 // Check for no curve selected.
 if (masterID == -1)
 {
  QMessageBox msgBox;
  msgBox.setText("Cannot create region:\n"
                 "No curve is selected.");
  msgBox.exec();
  return;
 }

 // Get number of selected lines.
 num_sel_curves = selInd.size() + 1;

 // Put the index of the master curve in a list of region curves.
 // First region point is the first point of the master curve.
 // Set the orientation of the first selected curve as true.
 // The orientation of curves is used to concatenate curves in a
 // consistent order along the region boundary.
 curveRegion.push_back(masterID);
 curveOrientation.push_back(true);
 double fst_x = m_curves[masterID]->getXinit();
 double fst_y = m_curves[masterID]->getYinit();
 double cur_x = m_curves[masterID]->getXend();
 double cur_y = m_curves[masterID]->getYend();

 // Check for a single closed curve, in which case create region.
 if( (fst_x == cur_x) && (fst_y == cur_y) )
 {
  // If closed curve is the only select, create a region.
  // Otherwise, abort region creation.
  if( num_sel_curves == 1 )
  {
   vector<Point> curvePts = m_curves[masterID]->getPointsToDraw();
   vector<Curve*> regionCurves;
   regionCurves.push_back(m_curves[masterID]);
   vector<bool> regionCurveOrients;
   // Check for closed curve points are in counter-clockwise order.
   // In any case, store region boundary points in counter-clockwise order.
   // Also removes the last point, since it it duplicates the first point.
   bool isCCW = CompGeom::isCounterClockwisePolygon( curvePts );
   vector<Point> regionPts;
   if( isCCW )
   {
    for (int j = 0; j < curvePts.size()-1; j++)
    {
     regionPts.push_back(curvePts[j]);
    }
    // Since the curve points are oriented in CCW order, set flag for
    // curve orientation with respect to region points as true.
    regionCurveOrients.push_back(true);
   } 
   else
   {
    for (int j = curvePts.size()-1; j > 0; j--)
    {
     regionPts.push_back(curvePts[j]);
    }
    // Since the curve points are oriented in CW order, set flag for
    // curve orientation with respect to region points as false.
    regionCurveOrients.push_back(false);
   }
   Region* region = new Region( regionPts,
                                regionCurves, regionCurveOrients );
   m_regions.push_back(region);
  }
  else
  {
   QMessageBox msgBox;
   msgBox.setText("Cannot create region:\n"
                  "Select only one closed curve.");
   msgBox.exec();
  }
  return;
 }

 // From this point on, at least two curves were selected.
 // Traverse list of selected curves trying to identify a closed and
 // countinous chain of curves just using curve end points.
 bool found_next_curve = false;
 do
 {
  double prv_x = cur_x;
  double prv_y = cur_y;
  found_next_curve = false;
  for (list <int>::iterator it = selInd.begin(); it != selInd.end(); it++)
  {
   double x1 = m_curves[*it]->getXinit();
   double y1 = m_curves[*it]->getYinit();
   double x2 = m_curves[*it]->getXend();
   double y2 = m_curves[*it]->getYend();
   // Check for closed curve, in which case abort region creation.
   if( (x1 == x2) && (y1 == y2) )
   {
    QMessageBox msgBox;
    msgBox.setText("Cannot create region:\n"
                   "Select only one closed curve.");
    msgBox.exec();
    return;
   }
   bool curve_orientation = true;
   if ((ABS(cur_x-x1) < ABSTOL) && (ABS(cur_y-y1) < ABSTOL))
   {
    cur_x = x2;
    cur_y = y2;
    curve_orientation = true;
    found_next_curve = true;
   }
   else if ((ABS(cur_x-x2) < ABSTOL) && (ABS(cur_y-y2) < ABSTOL))
   {
    cur_x = x1;
    cur_y = y1;
    curve_orientation = false;
    found_next_curve = true;
   }
   // If found curve along chain of curves, insert it in region and
   // remove it from list of selected curves.
   if (found_next_curve)
   {
    curveRegion.push_back(*it);
    it = selInd.erase(it);
    curveOrientation.push_back(curve_orientation);
    break;
   }
  }
 } while (found_next_curve);

 // Check whether number of selected curves is the same as the 
 // number of region curves.
 // Essentially, this is checking whether all selected curves form
 // a continuous chain.
 if (num_sel_curves != curveRegion.size())
 {
  QMessageBox msgBox;
  msgBox.setText("Cannot create region:\n"
                 "The selected curves do not form a continuous chain.");
  msgBox.exec();
  return;
 }

 // Check whether first point is equal to last curve point.
 if ((ABS(fst_x-cur_x) < ABSTOL) && (ABS(fst_y-cur_y) < ABSTOL))
 {
  // The selected curves form a polygon: a continuous and closed chain.
  // Collect the region boundary points from the curve points in a
  // consecutive order, respecting curve orientation with respect to the
  // first (masterID) selected curve:
  // If a curve orientation is the same as the first selected curve,
  // store region points in the same order of the traversed selected curve.
  // Otherwise, store region points in the reverse order of the traversed
  // selected curve.
  vector<Point> regionPts;
  vector<Curve*> regionCurves;
  for (int i = 0; i < curveRegion.size(); i++)
  {
   regionCurves.push_back(m_curves[curveRegion[i]]);
   vector<Point> curvePts = m_curves[curveRegion[i]]->getPointsToDraw();
   if (curveOrientation[i])
   {
    for (int j = 0; j < curvePts.size()-1; j++)
    {
     regionPts.push_back(curvePts[j]);
    }
   } 
   else
   {
    for (int j = curvePts.size()-1; j > 0 ; j--)
    {
     regionPts.push_back(curvePts[j]);
    }
   }
  }

  // Check whether the created closed sequence of points are in a
  // counter-clockwise order.  It that is not the case, revert
  // order of points.
  bool isCCW = CompGeom::isCounterClockwisePolygon( regionPts );
  if( !isCCW )
  {
   vector<Point> regionPtsInverted;
   for (int j = regionPts.size()-1; j >= 0 ; j--)
   {
    regionPtsInverted.push_back(regionPts[j]);
   }
   regionPts = regionPtsInverted;
  }

  // Since region boundary points are always stored in counter-clockwise
  // order, store in region a vector of curve orientations to indicate
  // that a curve orientation is in counter-clockwise order (true) or
  // in clockwise (false) order with respect the region boundary.
  vector<bool> regionCurveOrients;
  if( isCCW )
  {
   regionCurveOrients = curveOrientation;
  }
  else
  {
   vector<Curve*> regionCurvesInverted = regionCurves;
   regionCurves.clear();
   regionCurves.push_back(regionCurvesInverted[0]);
   if (curveOrientation[0])
    regionCurveOrients.push_back(false);
   else
    regionCurveOrients.push_back(true);
   for (int i = curveRegion.size()-1; i > 0; i--)
   {
    regionCurves.push_back(regionCurvesInverted[i]);
    if (curveOrientation[i])
     regionCurveOrients.push_back(false);
    else
     regionCurveOrients.push_back(true);
   }
  }

  // Create a new region with the boundary points, boundary curves
  // and boundary curves orientations.
  Region* region = new Region( regionPts,
                               regionCurves, regionCurveOrients );
  m_regions.push_back(region);
 }
 else
 {
  QMessageBox msgBox;
  msgBox.setText("Cannot create region:\n"
                 "The selected curves do not close off a region.");
  msgBox.exec();
  return;
 }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
MyModel::setNumSubdivOfSelectedCurves( int _nSdv )
{
 for(int i = 0; i < m_curves.size(); i++)
 {
  if (m_curves[i]->isSelected())
  {
    // Do not do anything if not changing number of subdivision of curve
   if(_nSdv == m_curves[i]->getNumberOfSubdiv())
    continue;

   m_curves[i]->setNumberOfSubdiv( _nSdv );

   // Check to see whether this curve is used by a region. If that is
   // the case, delete mesh of corresponding region.
   for(int j = 0; j < m_regions.size(); j++)
   {
    vector<Curve*> curvesRegion = m_regions[j]->getCurves();
    for(int k = 0; k < curvesRegion.size(); k++)
    {
     if(curvesRegion[k] == m_curves[i])
     {
      m_regions[j]->delMesh();
     }
    }
   }
  }
 }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
bool 
MyModel::getNumSubdivOfFirstSelectedCurve( int* _nSdv )
{
 for(int i = 0; i < m_curves.size(); i++)
 {
  if (m_curves[i]->isSelected())
  {
   *_nSdv = m_curves[i]->getNumberOfSubdiv();
   return true;
  }
 }
 return false;
}
//--------------------------------------------------------------------


//--------------------------------------------------------------------
void 
MyModel::generateMeshSelectedRegions( int _meshGenerationType )
{
 MeshGenerator* meshGenerator;

 switch( _meshGenerationType )
 {
  case MeshGenerator::TRANSFIN_BILINEAR:
   meshGenerator = new TransfinBilinear();
   break;
  case MeshGenerator::TRANSFIN_TRILINEAR:
   meshGenerator = new TransfinTrilinear();
   break;
  case MeshGenerator::DELAUNAY:
   meshGenerator = new Delaunay();
   break;
  default:
   return;
 }

 for(int i = 0; i < m_regions.size(); i++)
 {
  if (m_regions[i]->isSelected())
  {
   vector<vector<int>> loop = m_regions[i]->getCurveSdvs();
   if( meshGenerator->setParam(loop) )
   {
    vector<Point> bound = m_regions[i]->getCurveSdvPts();
    vector<Point> pts;
    vector<vector<int>> conn;
    if( meshGenerator->generateMesh( bound, pts, conn ) )
    {
     m_regions[i]->delMesh();
     Mesh* mesh = new Mesh( pts, conn );
     m_regions[i]->setMesh( mesh );
    }
   }
   else
   {
    QMessageBox msgBox;
    msgBox.setText("Cannot mesh region:\n"
           "The region curves/subdivisions are not consistent\n"
           "with the selected mesh generation algorithm.");
    msgBox.exec();
   }
  }
 }

 delete meshGenerator;
}
//--------------------------------------------------------------------
