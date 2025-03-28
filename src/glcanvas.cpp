#include <vector>
using namespace std;

#include "glcanvas.h"
#include "compgeom/tesselation.h"

#ifndef ABS
#define ABS(x) (((x) < 0.0)? -(x): (x))
#endif

//--------------------------------------------------------------------
GLCanvas::GLCanvas(QWidget *parent)
 : QGLWidget(parent)
{
 setMouseTracking(true);
 setFocusPolicy(Qt::ClickFocus);
 m_model = NULL;
 m_dspId = 0;
 m_updatedDsp = false;
 m_left = -1.0;
 m_right = 11.0;
 m_bottom = -1.0;
 m_top = 11.0;
 m_curMouseAction = GLCanvas::SELECTION;
 m_buttonPressed = false;
 m_mouseButton = Qt::NoButton;
 m_pt0.setX(0);
 m_pt0.setY(0);
 m_pt1.setY(0);
 m_pt1.setY(0);
 m_pickTolFac = 0.01;
 m_mouseMoveTol = 2;
 m_shiftKeyPressed = false;
 m_controlKeyPressed = false;
 m_colorBackground.setRGB(1.00,1.00,1.00);       // white
 m_colorCollecting.setRGB(0.75,0.00,0.75);       // dark magenta
 m_colorCurve.setRGB(0.50,0.50,0.00);            // dark yellow
 m_colorVertex.setRGB(0.00,0.50,0.50);           // dark cyan
 m_colorRegion.setRGB(0.75,0.75,0.75);           // light gray
 m_colorSelection.setRGB(1.00,0.00,0.00);        // red
 m_colorRegionSelection.setRGB(1.00,0.75,0.75);  // light red
 m_colorGrid.setRGB(0.00,0.00,0.00);             // black
 m_colorTessellation.setRGB(0.50,0.50,0.50);     // gray
 m_colorSdvPoint.setRGB(0.00,0.00,0.50);         // dark blue
 m_colorMesh.setRGB(0.00,0.00,0.00);             // black
 m_viewGrid = false;
 m_gridDspId = 0;
 m_updatedGridDsp = false;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
GLCanvas::~GLCanvas()
{
 if(m_dspId > 0)
  glDeleteLists(m_dspId, 1);
 if(m_gridDspId > 0)
  glDeleteLists(m_gridDspId, 1);
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GLCanvas::setModel(MyModel* _model)
{
 m_model = _model;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
GLCanvas::resetModelDisplay()
{
 if(m_model == NULL)
  return;
 m_updatedDsp = false;
 update();
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
GLCanvas::setMouseAction( int _action )
{
 if( m_curMouseAction == _action )
  return;

 switch( _action )
 {
  default:
  case GLCanvas::SELECTION:
   m_curMouseAction = GLCanvas::SELECTION;
   m_collector.reset();
   break;
  case GLCanvas::COLLECTION:
   m_curMouseAction = GLCanvas::COLLECTION;
   break;
 }
 update();
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
GLCanvas::setCurveType( int _type )
{
 if( (m_curMouseAction == GLCanvas::COLLECTION) &&
     (m_collector.getCurveType() == _type) )
  return;

 m_collector.reset();
 m_collector.setCurveType( _type );
 update();
}
//--------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
GLCanvas::setGridSnapData( bool _viewGrid, bool _isSnapOn,
                          double _dx, double _dy )
{
 m_grid.setSnapData( _isSnapOn, _dx, _dy );
 m_viewGrid = _viewGrid;
 m_updatedGridDsp = false;
 update();
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool 
GLCanvas::getGridSnapInfo( double* _dx, double* _dy )
{
 m_grid.getGridSpace( _dx, _dy );
 return m_grid.getSnapInfo();
}
//-------------------------------------------------------------------------

//--------------------------------------------------------------------
void 
GLCanvas::delSelectedEntities()
{
 if( (m_model != NULL) && (!m_model->isEmpty()) )
 {
  m_model->delSelectedCurves();
  m_model->delSelectedRegions();
  m_updatedDsp = false;
  update();
 }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
GLCanvas::intersectTwoSelectedCurves()
{
 if( (m_model != NULL) && (!m_model->isEmpty()) )
 {
  m_model->intersectTwoSelectedCurves();
  m_updatedDsp = false;
  update();
 }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
GLCanvas::createRegion()
{
 if( (m_model != NULL) && (!m_model->isEmpty()) )
 {
  m_model->createRegion();
  m_updatedDsp = false;
  update();
 }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GLCanvas::initializeGL()
{
 // Set white as background color and clear window
 glClearColor(m_colorBackground.getR(),
              m_colorBackground.getG(),
              m_colorBackground.getB(), 1.0);
 glClear(GL_COLOR_BUFFER_BIT);

 // enable smooth line display
 glEnable(GL_LINE_SMOOTH);
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GLCanvas::resizeGL(int _width, int _height)
{
 // Avoid division by zero
 if(_width == 0) _width = 1;

 // Store GL canvas sizes in object properties
 m_w = _width;
 m_h = _height;

 // Setup world space window limits based on model bounding box
 if( (m_model != NULL) && (!m_model->isEmpty()) )
 {
  m_model->getBoundBox(&m_left, &m_right, &m_bottom, &m_top);
  scaleWorldWindow(1.10);
 }
 else
 {
  scaleWorldWindow(1.0);
 }

 // Setup the viewport to canvas dimensions
 glViewport(0, 0, (GLint)m_w, (GLint)m_h);

 // Reset the coordinate system
 glMatrixMode(GL_PROJECTION); 
 glLoadIdentity();

 // Establish the clipping volume by setting up an
 // orthographic projection
 glOrtho(m_left, m_right, m_bottom, m_top, -1.0, 1.0);

 // Setup display in model coordinates
 glMatrixMode(GL_MODELVIEW); 
 glLoadIdentity();
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GLCanvas::paintGL()
{
 // Clear the buffer with the current clear color
 glClear(GL_COLOR_BUFFER_BIT);

 // Display model (if there is one)
 if( (m_model != NULL) && (!m_model->isEmpty()) )
 {
  if(!m_updatedDsp)
  {
   if(m_dspId > 0)
    glDeleteLists(m_dspId, 1);
   m_dspId = makeDisplayModel();
  }
  if(m_dspId > 0)
  {
   glCallList(m_dspId);
   m_updatedDsp = true;
  }
 }

 // display grid (if it is visible)
 if( m_viewGrid )
 {
  if(!m_updatedGridDsp)
  {
   if(m_gridDspId > 0)
    glDeleteLists(m_gridDspId, 1);
   m_gridDspId = makeDisplayGrid();
  }
  if(m_gridDspId > 0)
  {
   glCallList(m_gridDspId);
   m_updatedGridDsp = true;
  }
 }

 switch( m_curMouseAction )
 {
  case GLCanvas::SELECTION:
   {
    // Check to see whether there is selection fence and,
    // if that is the case, draw it
    GLuint col_fence = drawSelectionFence();
    if(col_fence > 0)
    {
     glCallList(col_fence);
     glDeleteLists(col_fence, 1);
    }
   }
   break;
  case GLCanvas::COLLECTION:
   {
    // Check to see whether there is a curve being collected and,
    // if that is the case, draw it
    GLuint col_curve = drawCollectedCurve();
    if(col_curve > 0)
    {
     glCallList(col_curve);
     glDeleteLists(col_curve, 1);
    }
   }
  break;
 }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
GLuint 
GLCanvas::makeDisplayModel()
{
 if( (m_model == NULL) || m_model->isEmpty() )
  return 0;

 GLuint list = glGenLists(1);
 glNewList(list, GL_COMPILE);

 // draw regions
 vector<Region*> pRegions = m_model->getRegions();
//  for(int i = 0; i < pRegions.size(); i++)
//  {
//   if( pRegions[i]->isSelected() )
//    glColor3d( m_colorRegionSelection.getR(),
//               m_colorRegionSelection.getG(),
//               m_colorRegionSelection.getB() );
//   else
//    glColor3d( m_colorRegion.getR(),
//               m_colorRegion.getG(),
//               m_colorRegion.getB() );
//   vector<Point> pts = pRegions[i]->getPoints();
//   glBegin(GL_POLYGON);
//   for (int j = 0; j < pts.size(); j++)
//   {
//    glVertex2d(pts[j].getX(), pts[j].getY());
//   }
//   glEnd();
//  }
 for(int i = 0; i < pRegions.size(); i++)
 {
  if( pRegions[i]->isSelected() )
   glColor3d( m_colorRegionSelection.getR(),
              m_colorRegionSelection.getG(),
              m_colorRegionSelection.getB() );
  else
   glColor3d( m_colorRegion.getR(),
              m_colorRegion.getG(),
              m_colorRegion.getB() );
  vector<Point> pts = pRegions[i]->getPoints();
  vector<vector<int> > triangs;
  Tesselation::triangleParing( pts, triangs );
  for(int j = 0; j < triangs.size(); j++ )
  {
   glBegin(GL_TRIANGLES);
   glVertex2d(pts[triangs[j][0]].getX(), pts[triangs[j][0]].getY());
   glVertex2d(pts[triangs[j][1]].getX(), pts[triangs[j][1]].getY());
   glVertex2d(pts[triangs[j][2]].getX(), pts[triangs[j][2]].getY());
   glEnd();
  }
//   Display tessellation lines (used for educational purposes)
//   glColor3d( m_colorTessellation.getR(),
//              m_colorTessellation.getG(),
//              m_colorTessellation.getB() );
//   for(int j = 0; j < triangs.size(); j++ )
//   {
//    glBegin( GL_LINE_LOOP );
//    glVertex2d(pts[triangs[j][0]].getX(), pts[triangs[j][0]].getY());
//    glVertex2d(pts[triangs[j][1]].getX(), pts[triangs[j][1]].getY());
//    glVertex2d(pts[triangs[j][2]].getX(), pts[triangs[j][2]].getY());
//    glEnd();
//   }
 }

 // draw region meshes
 drawRegionMeshes();

 // draw curves
 glLineWidth(1.0);
 vector<Curve*> pCurves = m_model->getCurves();
 for( int i = 0; i < pCurves.size(); i++ )
 {
  vector<Point> pts = pCurves[i]->getPointsToDraw();
  vector<Point> sdvPts = pCurves[i]->getSubdivPoints();

  // display curve lines
  if( pCurves[i]->isSelected() )
   glColor3d( m_colorSelection.getR(),
              m_colorSelection.getG(),
              m_colorSelection.getB() );
  else
   glColor3d( m_colorCurve.getR(),
              m_colorCurve.getG(),
              m_colorCurve.getB() );
  glBegin(GL_LINE_STRIP);
  for( int j = 0; j < pts.size(); j++ )
  {
   glVertex2d((GLdouble)pts[j].getX(),
              (GLdouble)pts[j].getY());
  }
  glEnd();

  // display subdivision points
  if(sdvPts.size() > 2)
  {
   glPointSize(5.0);
   glColor3d( m_colorSdvPoint.getR(),
              m_colorSdvPoint.getG(),
              m_colorSdvPoint.getB() );
   glBegin(GL_POINTS);
   for( int j = 1; j < sdvPts.size()-1; j++ )
   {
    glVertex2d((GLdouble)sdvPts[j].getX(),
               (GLdouble)sdvPts[j].getY());
   }
   glEnd();
  }

  // display curve vertices
  glPointSize(5.0);
  glColor3d( m_colorVertex.getR(),
             m_colorVertex.getG(),
             m_colorVertex.getB() );
  glBegin(GL_POINTS);
  glVertex2d((GLdouble)pts[0].getX(),
             (GLdouble)pts[0].getY());
  glVertex2d((GLdouble)pts[pts.size()-1].getX(),
             (GLdouble)pts[pts.size()-1].getY());
  glEnd();
 }

 glEndList();
 return list;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void  
GLCanvas::drawRegionMeshes()
{
 Mesh* mesh;
 vector<Region*> pRegions = m_model->getRegions();
 glLineWidth(0.5);
 glColor3d( m_colorMesh.getR(),
            m_colorMesh.getG(),
            m_colorMesh.getB() );
 for(int i = 0; i < pRegions.size(); i++)
 {
  mesh = pRegions[i]->getMesh();
  if( mesh != NULL )
  {
   vector<Point> pts = mesh->getPts();
   vector<vector<int>> conn = mesh->getConn();
   for(int j = 0; j < conn.size(); j++)
   {
    vector<int> elem = conn[j];
    glBegin(GL_LINE_LOOP);
    for(int k = 0; k < elem.size(); k++)
    {
     glVertex2d(pts[elem[k]].getX(), pts[elem[k]].getY());
    }
    glEnd();
   }
  }
 }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
GLuint 
GLCanvas::drawSelectionFence()
{
 // It is assumed that the current mouse action is for curve selection

 // Only draw a fence if mouse button is pressed
 if( !m_buttonPressed )
  return 0;

 // If current mouse point is in the same position of initial mouse point
 // do not display anything
 if( (m_pt0.x() == m_pt1.x()) && (m_pt0.y() == m_pt1.y()) )
  return 0;

// If there is no model or it is empty, do nothing
 if( (m_model == NULL) || m_model->isEmpty() )
  return 0;

 // Display a fence from initial mouse point to current mouse point
 GLuint list = glGenLists(1);
 glNewList(list, GL_COMPILE);

 glLineWidth(1.0);
 glColor3d( m_colorSelection.getR(),
            m_colorSelection.getG(),
            m_colorSelection.getB() );
 glBegin(GL_LINE_STRIP);
 QPointF pt0W = convertPtCoordsToUniverse( m_pt0 );
 QPointF pt1W = convertPtCoordsToUniverse( m_pt1 );
 glVertex2d((GLdouble)pt0W.x(), (GLdouble)pt0W.y());
 glVertex2d((GLdouble)pt1W.x(), (GLdouble)pt0W.y());
 glVertex2d((GLdouble)pt1W.x(), (GLdouble)pt1W.y());
 glVertex2d((GLdouble)pt0W.x(), (GLdouble)pt1W.y());
 glVertex2d((GLdouble)pt0W.x(), (GLdouble)pt0W.y());
 glEnd();

 glEndList();
 return list;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
GLuint 
GLCanvas::drawCollectedCurve()
{
 // It is assumed that the current mouse action if for curve collection

 if( (!m_collector.isActive()) || (!m_collector.isCollecting()) )
  return 0;

 GLuint list = glGenLists(1);
 glNewList(list, GL_COMPILE);

 glLineWidth(1.0);
 glColor3d( m_colorCollecting.getR(),
            m_colorCollecting.getG(),
            m_colorCollecting.getB() );

 // Display lines of curve being collected
 glBegin(GL_LINE_STRIP);
 vector<Point> pts = m_collector.getDrawPoints();
 for( int j = 0; j < pts.size(); j++ )
 {
  double x = pts[j].getX();
  double y = pts[j].getY();
  glVertex2d((GLdouble)x, (GLdouble)y);
 }
 glEnd();

 // Display control points of curve being collected
 glPointSize(5.0);
 glBegin(GL_POINTS);
 vector<Point> ctrl_pts = m_collector.getPoints();
 for( int j = 0; j < ctrl_pts.size(); j++ )
 {
  double x = ctrl_pts[j].getX();
  double y = ctrl_pts[j].getY();
  glVertex2d((GLdouble)x, (GLdouble)y);
 }
 glEnd();

 glEndList();
 return list;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GLCanvas::scaleWorldWindow(double _scaleFac)
{
 double vpr;          // viewport distortion ratio
 double cx, cy,c;       // window center
 double sizex, sizey; // window sizes

 //Compute canvas viewport ratio.
 vpr = (double)m_h / (double)m_w;

 // Get current window center.
 /*** COMPLETE HERE - GLCANVAS: 01 ***/
 cx = (m_right + m_left) / 2;
 cy = (m_top + m_bottom) / 2;

 /*** COMPLETE HERE - GLCANVAS: 01 ***/

 // Set new window sizes based on scaling factor.
 /*** COMPLETE HERE - GLCANVAS: 02 ***/
 sizex = _scaleFac*abs(m_right - m_left);
 sizey = _scaleFac*abs(m_top - m_bottom);

 /*** COMPLETE HERE - GLCANVAS: 02 ***/

 // Adjust window to keep the same aspect ratio of the viewport.
 /*** COMPLETE HERE - GLCANVAS: 03 ***/

 // Encontre o menor lado
 c = sizey / sizex;

 if ((c > vpr)) // x é o menor lado logo não é alterado
 {
	 sizex = sizey / vpr;
 }
 else if ((c > vpr)) // y é o menor lado logo não é alterado
 {
	 sizey = (vpr)*sizey;
 }
 c = (sizey / sizex);

 m_right = cx + (sizex / 2);
 m_left = cx - (sizex / 2);
 m_bottom = cy - (sizey / 2);
 m_top = cy + (sizey / 2);



 /*** COMPLETE HERE - GLCANVAS: 03 ***/

 // Establish the clipping volume by setting up an
 // orthographic projection
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(m_left, m_right, m_bottom, m_top, -1.0, 1.0);
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GLCanvas::panWorldWindow(double _panFacX, double _panFacY)
{
	// Compute pan distances in horizontal and vertical directions.
	double panX = (m_right - m_left)   * _panFacX;
	double panY = (m_top - m_bottom) * _panFacY;

	// Shift current window.
	/*** COMPLETE HERE - GLCANVAS: 04 ***/

	m_right = m_right + panX;
	m_left = m_left + panX;
	m_top = m_top + panY;
	m_bottom = m_bottom + panY;


	/*** COMPLETE HERE - GLCANVAS: 04 ***/

	// Establish the clipping volume by setting up an
	// orthographic projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(m_left, m_right, m_bottom, m_top, -1.0, 1.0);
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GLCanvas::fitWorldToViewport()
{
	if (!m_model)
		return;
	m_model->getBoundBox(&m_left, &m_right, &m_bottom, &m_top); //BoundBox inicial
	scaleWorldWindow(1.10);
	update();
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GLCanvas::zoomIn()
{
	if (!m_model)
		return;
	/*** COMPLETE HERE - GLCANVAS: 05 ***/
	scaleWorldWindow(0.9);
	update();
	/*** COMPLETE HERE - GLCANVAS: 05 ***/
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GLCanvas::zoomOut()
{
	if (!m_model)
		return;
	/*** COMPLETE HERE - GLCANVAS: 06 ***/
	scaleWorldWindow(1.10);
	update();
	/*** COMPLETE HERE - GLCANVAS: 06 ***/
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GLCanvas::panLeft()
{
	if (!m_model)
		return;
	/*** COMPLETE HERE - GLCANVAS: 07 ***/
	panWorldWindow(-0.1, 0);
	update();
	/*** COMPLETE HERE - GLCANVAS: 07 ***/
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GLCanvas::panRight()
{
	if (!m_model)
		return;
	/*** COMPLETE HERE - GLCANVAS: 08 ***/
	panWorldWindow(0.1, 0);
	update();

	/*** COMPLETE HERE - GLCANVAS: 08 ***/
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GLCanvas::panDown()
{
	if (!m_model)
		return;
	/*** COMPLETE HERE - GLCANVAS: 09 ***/
	panWorldWindow(0, -0.1);
	update();
	/*** COMPLETE HERE - GLCANVAS: 09 ***/
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GLCanvas::panUp()
{
	if (!m_model)
		return;
	/*** COMPLETE HERE - GLCANVAS: 10 ***/
	panWorldWindow(0, 0.1);
	update();

	/*** COMPLETE HERE - GLCANVAS: 10 ***/
}
//--------------------------------------------------------------------

GLuint 
GLCanvas::makeDisplayGrid()
{
 double oX = 0.0;
 double oY = 0.0;
 double x = m_left;
 double y = m_bottom;
 double gridX;
 double gridY;

 m_grid.getGridSpace( &gridX, &gridY );

 GLuint list = glGenLists(1);
 glNewList(list, GL_COMPILE);

 glColor3d( m_colorGrid.getR(),
            m_colorGrid.getG(),
            m_colorGrid.getB() );

 // display grid points
 glPointSize(1.0);
 glBegin(GL_POINTS);
 x = oX - ((int)((oX - m_left)/gridX) * gridX) - gridX;
 while( x <= m_right )
 {
  y = oY - ((int)((oY - m_bottom)/gridY) * gridY) - gridY;
  while( y <= m_top )
  {
   glVertex2d((GLdouble)x, (GLdouble)y);
   y += gridY;
  }
  x += gridX;
 }
 glEnd();

 // display crossed lines at origin
 glLineWidth(1.0);
 glBegin(GL_LINES);
 x = oX - gridX*0.5;
 y = oY;
 glVertex2d((GLdouble)x, (GLdouble)y);
 x = oX + gridX*0.5;
 y = oY;
 glVertex2d((GLdouble)x, (GLdouble)y);
 x = oX;
 y = oY - gridY*0.5;
 glVertex2d((GLdouble)x, (GLdouble)y);
 x = oX;
 y = oY + gridY*0.5;
 glVertex2d((GLdouble)x, (GLdouble)y);
 glEnd();

 glEndList();
 return list;
}
//-------------------------------------------------------------------------

//--------------------------------------------------------------------
QPointF 
GLCanvas::convertPtCoordsToUniverse(QPoint _pt)
{
 double dX = m_right - m_left; // universe window horizontal size
 double dY = m_top - m_bottom; // universe window vertical size

 // Origin of canvas raster coordinates it at the left-top corner,
 // while origin of GL canvas floating point coordinates is at
 // left-bottom corner.
 // mX is the distance of point to left universe window limit
 // mY is the distance of point to bottom universe window limit
 double mX = (double)_pt.x()*dX/(double)m_w;
 double mY = (double)(m_h - _pt.y())*dY/(double)m_h; 

 double x = m_left + mX;
 double y = m_bottom + mY;
 return QPointF(x,y);
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
//                      MOUSE EVENT SLOTS
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
GLCanvas::mousePressEvent(QMouseEvent* event)
{
 m_buttonPressed = true;
 m_pt0 = event->pos();
 m_mouseButton = event->button();
 switch( m_curMouseAction )
 {
  default:
  case GLCanvas::SELECTION:
   break;
  case GLCanvas::COLLECTION:
   if( !m_collector.isActive() )
   {
    // In case of left mouse button, if not doing any curve collection,
    // start a new curve collection
    if( m_mouseButton == Qt::LeftButton )
    {
     m_collector.startCurveCollection();
    }
   }
   break;
 }
}

//--------------------------------------------------------------------
void 
GLCanvas::mouseMoveEvent(QMouseEvent* event)
{
 // Get current mouse position
 m_pt1 = event->pos();

 // Treat mouse move event according to current mouse action type
 switch( m_curMouseAction )
 {
  default:
   break;
  case GLCanvas::SELECTION:
   // Disregard mouse move event if left mouse button is not pressed
   if( (m_mouseButton == Qt::LeftButton) && m_buttonPressed )
   {
    update();
   }
   break;
  case GLCanvas::COLLECTION:
   // Only consider current point if left mouse button was used,
   // if not button pressed, and if current point is not at the
   // same location of button press point.
   if( m_mouseButton == Qt::LeftButton && (!m_buttonPressed) )
   {
    if( (ABS(m_pt0.x() - m_pt1.x()) > m_mouseMoveTol) ||
        (ABS(m_pt0.y() - m_pt1.y()) > m_mouseMoveTol) )
    {
     if( m_collector.isCollecting() )
     {
      // Convert current mouse position point to world coordinates
      QPointF pt1W = convertPtCoordsToUniverse( m_pt1 );
      double xW = pt1W.x();
      double yW = pt1W.y();
      // Snap point to grid (if it is visible). Also check for
      // snap-to-grid flag (which will be inverted by control key).
      if( m_viewGrid )
      {
       bool isSnapOn = m_grid.getSnapInfo();
       if( (!m_controlKeyPressed && isSnapOn) ||
           (m_controlKeyPressed && !isSnapOn) )
       {
        m_grid.snapTo( &xW, &yW );
       }
      }
      // Try to attract point to a curve
      if( (m_model) && (!m_model->isEmpty()) )
      {
       double max_size = ((m_right-m_left) > (m_top-m_bottom) ) ?
                          (m_right-m_left) : (m_top-m_bottom);
       double pick_tol = max_size * m_pickTolFac;
       m_model->snapToCurve( &xW, &yW, pick_tol );
      }
      // Add point as a temporary point for curve collection.
      m_collector.addTempPoint(xW, yW);
      update();
     }
    }
   }
   break;
 }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
GLCanvas::mouseReleaseEvent(QMouseEvent *event)
{
 m_buttonPressed = false;

 // Get current mouse position
 m_pt1 = event->pos();

 // Convert mouse positions to world coordinates
 QPointF pt0W = convertPtCoordsToUniverse( m_pt0 );
 QPointF pt1W = convertPtCoordsToUniverse( m_pt1 );

 // Treat mouse release event according to current mouse action type
 switch( m_curMouseAction )
 {
  default:
   break;
  case GLCanvas::SELECTION:
   if( m_mouseButton == Qt::LeftButton )
   {
    // If there is a model and it is not empty
    if( (m_model != NULL) && (!m_model->isEmpty()) )
    {
     // If current mouse point is in the same position of inital mouse point,
     // consider a mouse pick selection.
     // Otherwise, consider a mouse fence selection.
     if( (ABS(m_pt0.x() - m_pt1.x()) <= m_mouseMoveTol) &&
         (ABS(m_pt0.y() - m_pt1.y()) <= m_mouseMoveTol) )
     {
      double max_size = ((m_right-m_left) > (m_top-m_bottom) ) ?
                         (m_right-m_left) : (m_top-m_bottom);
      double pick_tol = max_size * m_pickTolFac;
      m_model->selectPick( pt1W.x(), pt1W.y(), pick_tol, m_shiftKeyPressed );
     }
     else
     {
      double xmin = (pt0W.x() < pt1W.x()) ? pt0W.x() : pt1W.x();
      double xmax = (pt0W.x() > pt1W.x()) ? pt0W.x() : pt1W.x();
      double ymin = (pt0W.y() < pt1W.y()) ? pt0W.y() : pt1W.y();
      double ymax = (pt0W.y() > pt1W.y()) ? pt0W.y() : pt1W.y();
      m_model->selectFence( xmin, xmax, ymin, ymax, m_shiftKeyPressed );
     }
    }
    m_updatedDsp = false;
    update();
   }
   break;
  case GLCanvas::COLLECTION:
   // Only consider current point if left mouse point was used and
   // if it is on the same location of button press point.
   if( m_mouseButton == Qt::LeftButton )
   {
    if( (ABS(m_pt0.x() - m_pt1.x()) <= m_mouseMoveTol) &&
        (ABS(m_pt0.y() - m_pt1.y()) <= m_mouseMoveTol) )
    {
     double max_size = ((m_right-m_left) > (m_top-m_bottom) ) ?
                        (m_right-m_left) : (m_top-m_bottom);
     double pick_tol = max_size * m_pickTolFac;
     double xW = pt1W.x();
     double yW = pt1W.y();
     // Snap point to grid (if it is visible). Also check for
     // snap-to-grid flag (which will be inverted by control key).
     if( m_viewGrid )
     {
      bool isSnapOn = m_grid.getSnapInfo();
      if( (!m_controlKeyPressed && isSnapOn) ||
          (m_controlKeyPressed && !isSnapOn) )
      {
       m_grid.snapTo( &xW, &yW );
      }
     }
     // Try to attract point to a curve
     if( (m_model) && (!m_model->isEmpty()) )
     {
      m_model->snapToCurve( &xW, &yW, pick_tol );
     }
     // Add point to collected curve.
     m_collector.insertPoint(xW, yW, pick_tol);
    }
   }

   // Check for end of curve collection, which occurs in two situations:
   // (a) If left mouse button was used, and current collected curve has
   //     a limit in the number of points, verify whether current point
   //     finishes collection of current curve.
   // (b) If right mouse button was used, and current collected curve has
   //     no limit in the number of points, verify whether previously
   //     collected points can finish collection of current curve.
   bool endCollection = false;
   if( m_mouseButton == Qt::LeftButton )
   {
    if( !m_collector.isUnlimited() )
    {
     if( m_collector.hasFinished() )
     {
      endCollection = true;
     }
    }
   }
   else if( m_mouseButton == Qt::RightButton )
   {
    if( m_collector.isUnlimited() )
    {
     if( m_collector.hasFinished() )
     {
      endCollection = true;
     }
     else
     {
      // If right mouse button was used, curve has an unlimited number of points, and
      // previously collected points cannot finish collection of curve, reset current
      // curve collection
      m_collector.reset();
      update();
     }
    }
    else
    {
     // If right mouse button was used and curve has a limited number of points,
     // reset current curve collection
     m_collector.reset();
     update();
    }
   }
   if( endCollection )
   {
    Curve* curve = m_collector.getCollectedCurve();
    m_model->insertCurve( curve );
    m_collector.endCurveCollection();
    m_updatedDsp = false;
    update();
   }
   break;
 }
}

//--------------------------------------------------------------------
void 
GLCanvas::keyPressEvent( QKeyEvent * event )
{
 m_shiftKeyPressed = (event->key() == Qt::Key_Shift);
 m_controlKeyPressed = (event->key() == Qt::Key_Control);
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void 
GLCanvas::keyReleaseEvent( QKeyEvent * event )
{
 m_shiftKeyPressed = false;
 m_controlKeyPressed = false;
}
//--------------------------------------------------------------------
