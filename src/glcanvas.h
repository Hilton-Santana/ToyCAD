#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <QMouseEvent>
#include <QtOpenGL/QGLWidget>

#include "color.h"
#include "mymodel.h"
#include "curvecollector.h"
#include "grid.h"

class GLCanvas : public QGLWidget
{
 Q_OBJECT // must include this if you use Qt Signals & Slots

 public:
  enum MouseActionType{ UNDEFINED, SELECTION, COLLECTION };

  GLCanvas(QWidget *parent = 0);
  ~GLCanvas();

  void     setModel(MyModel* _model);
  MyModel* getModel() { return m_model; };
  void     resetModelDisplay();
  void     setMouseAction( int _action );
  void     setCurveType( int _type );
  void     setGridSnapData( bool _viewGrid, bool _isSnapOn,
                            double _dx, double _dy );
  bool     getGridSnapInfo( double* _dx, double* _dy );
  void     delSelectedEntities();
  void     intersectTwoSelectedCurves();
  void     createRegion();

 protected:
  // Canvas predefined slots
  void     initializeGL();
  void     resizeGL(int _width, int _height);
  void     paintGL();

  // Display functions
  GLuint   makeDisplayModel();
  void     drawRegionMeshes();
  GLuint   drawSelectionFence();
  GLuint   drawCollectedCurve();

  // Functions to manage visualization window limits
  void     scaleWorldWindow(double _scaleFac);
  void     panWorldWindow(double _panFacX, double _panFacY);

 public:
  void     fitWorldToViewport();
  void     zoomIn();
  void     zoomOut();
  void     panLeft();
  void     panRight();
  void     panDown();
  void     panUp();

 protected:
  MyModel* m_model;          // model to be displayed
  GLuint m_dspId;            // GL list index for model display
  bool m_updatedDsp;         // if true, model display is updated
  CurveCollector m_collector;// Collector of entities on canvas
  Grid m_grid;               // Background modeling grid;

  int m_w;                   // width: GL canvas horizontal size
  int m_h;                   // height: GL canvas vertical size
  GLdouble m_left;           // left limit of object space window
  GLdouble m_right;          // right limit of object space window
  GLdouble m_bottom;         // bottom limit of object space window
  GLdouble m_top;            // top limit of object space window

  // Defined colors
  Color m_colorBackground;
  Color m_colorCollecting;
  Color m_colorRegion;
  Color m_colorCurve;
  Color m_colorVertex;
  Color m_colorSelection;
  Color m_colorRegionSelection;
  Color m_colorGrid;
  Color m_colorTessellation;
  Color m_colorSdvPoint;
  Color m_colorMesh;

  // Grid display data and methods
  bool m_viewGrid;
  GLuint m_gridDspId;       // GL list index for grid display
  bool m_updatedGridDsp;    // if true, grid display is updated
  GLuint makeDisplayGrid();

  // Mouse point properties
  int m_curMouseAction;     // current mouse action type
  bool m_buttonPressed;     // if true, mouse button is pressed
  // mouse button that was pressed:
  //(Qt::LeftButton, Qt::RightButton, or Qt::MidButton)
  Qt::MouseButton m_mouseButton;
  // QPoint is a Qt class that defines a point in a plane
  // i.e. the position of the mouse on the canvas.
  QPoint m_pt0;             // mouse position at button press event
  QPoint m_pt1;             // current mouse position
  double m_pickTolFac;      // factor for pick tolerance
  int m_mouseMoveTol;       // tolerance for mouse move

  // Pressed key properties
  bool m_shiftKeyPressed;
  bool m_controlKeyPressed;

  // QPointF is a Qt class that defines a point in floating
  // point coordinates.
  QPointF convertPtCoordsToUniverse(QPoint _pt);

 public slots:
  // Mouse events slots
  void mousePressEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  // Keyboard event slot
  void keyPressEvent( QKeyEvent* event );
  void keyReleaseEvent( QKeyEvent* event );
};

#endif // GLCANVAS_H
