#include "myapp.h"
#include "glcanvas.h"
#include "mesh/meshgenerator.h"

//--------------------------------------------------------------------
MyApp::MyApp(QWidget *parent)
	: QMainWindow(parent)
{
 ui.setupUi(this);

 // create a model object and pass a pointer to it to canvas object
 m_model = new MyModel();
 ui.glcanvas->setModel(m_model);

 // create and setup the dialog responsible for the grid and snap options
 m_gridDialog = new QDialog;
 m_gridDlg.setupUi( m_gridDialog );

 // Set default button checked status
 ui.actionSelect->setChecked(true);
 ui.actionLine->setChecked(false);
 ui.actionPolyLine->setChecked(false);
 ui.actionCubicBezier->setChecked(false);

 // set default mouse action on canvas
 ui.glcanvas->setMouseAction( GLCanvas::SELECTION );
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
MyApp::~MyApp()
{
 delete m_gridDialog;
 delete m_model;
}
//--------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
MyApp::on_actionSelect_triggered()
{
 ui.actionSelect->setChecked(true);
 ui.actionLine->setChecked(false);
 ui.actionPolyLine->setChecked(false);
 ui.actionQuadBezier->setChecked(false);
 ui.actionCubicBezier->setChecked(false);
 ui.actionCircle->setChecked(false);
 ui.actionCircleArc->setChecked(false);
 // set corresponding mouse action on canvas
 ui.glcanvas->setMouseAction( GLCanvas::SELECTION );
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
MyApp::on_actionLine_triggered()
{
 ui.actionSelect->setChecked(false);
 ui.actionLine->setChecked(true);
 ui.actionPolyLine->setChecked(false);
 ui.actionQuadBezier->setChecked(false);
 ui.actionCubicBezier->setChecked(false);
 ui.actionCircle->setChecked(false);
 ui.actionCircleArc->setChecked(false);
 // set corresponding mouse action on canvas
 ui.glcanvas->setMouseAction( GLCanvas::COLLECTION );
 ui.glcanvas->setCurveType( Curve::LINE );
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void
MyApp::on_actionPolyLine_triggered()
{
	ui.actionSelect->setChecked(false);
	ui.actionLine->setChecked(false);
	ui.actionPolyLine->setChecked(true);
	ui.actionQuadBezier->setChecked(false);
	ui.actionCubicBezier->setChecked(false);
	ui.actionCircle->setChecked(false);
	ui.actionCircleArc->setChecked(false);
	// set corresponding mouse action on canvas
	ui.glcanvas->setMouseAction(GLCanvas::COLLECTION);
	ui.glcanvas->setCurveType(Curve::POLYLINE);
}
//-------------------------------------------------------------------------
void
MyApp::on_actionQuadBezier_triggered()
{
	ui.actionSelect->setChecked(false);
	ui.actionLine->setChecked(false);
	ui.actionPolyLine->setChecked(false);
	ui.actionQuadBezier->setChecked(true);
	ui.actionCubicBezier->setChecked(false);
	ui.actionCircle->setChecked(false);
	ui.actionCircleArc->setChecked(false);
	// set corresponding mouse action on canvas
	ui.glcanvas->setMouseAction(GLCanvas::COLLECTION);
	ui.glcanvas->setCurveType(Curve::QUADBEZIER);
}
//-------------------------------------------------------------------------
void
MyApp::on_actionCubicBezier_triggered()
{
	ui.actionSelect->setChecked(false);
	ui.actionLine->setChecked(false);
	ui.actionPolyLine->setChecked(false);
	ui.actionQuadBezier->setChecked(false);
	ui.actionCubicBezier->setChecked(true);
	ui.actionCircle->setChecked(false);
	ui.actionCircleArc->setChecked(false);
	// set corresponding mouse action on canvas
	ui.glcanvas->setMouseAction(GLCanvas::COLLECTION);
	ui.glcanvas->setCurveType(Curve::CUBICBEZIER);
}
//-------------------------------------------------------------------------
void
MyApp::on_actionCircle_triggered()
{
	ui.actionSelect->setChecked(false);
	ui.actionLine->setChecked(false);
	ui.actionPolyLine->setChecked(false);
	ui.actionQuadBezier->setChecked(false);
	ui.actionCubicBezier->setChecked(false);
	ui.actionCircle->setChecked(true);
	ui.actionCircleArc->setChecked(false);
	// set corresponding mouse action on canvas
	ui.glcanvas->setMouseAction(GLCanvas::COLLECTION);
	ui.glcanvas->setCurveType(Curve::CIRCLE);
}
//-------------------------------------------------------------------------
void
MyApp::on_actionCircleArc_triggered()
{
	ui.actionSelect->setChecked(false);
	ui.actionLine->setChecked(false);
	ui.actionPolyLine->setChecked(false);
	ui.actionQuadBezier->setChecked(false);
	ui.actionCubicBezier->setChecked(false);
	ui.actionCircle->setChecked(false);
	ui.actionCircleArc->setChecked(true);
	// set corresponding mouse action on canvas
	ui.glcanvas->setMouseAction(GLCanvas::COLLECTION);
	ui.glcanvas->setCurveType(Curve::CIRCLEARC);
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
MyApp::on_actionGrid_triggered()
{
 // verifies if the grid button is turned on or off
 bool viewGrid = ui.actionGrid->isChecked();
 // get data from grid/snap and set in the dialog
 double dx = 0.0;
 double dy = 0.0;
 bool isSnapOn = ui.glcanvas->getGridSnapInfo( &dx, &dy );
 QString sdx;
 sdx.setNum( dx );
 m_gridDlg.lineEditXdir->clear();
 m_gridDlg.lineEditXdir->insert( sdx );
 QString sdy;
 sdy.setNum( dy );
 m_gridDlg.lineEditYdir->clear();
 m_gridDlg.lineEditYdir->insert( sdy );
 m_gridDlg.checkBoxSnap->setChecked( viewGrid );
 if( viewGrid )
 {
  // opens dialog and get info from grid and snap
  if( m_gridDialog->exec() == QDialog::Accepted )
  {
   // set info to activate grid and snap
   sdx = m_gridDlg.lineEditXdir->text();
   sdy = m_gridDlg.lineEditYdir->text();
   isSnapOn = m_gridDlg.checkBoxSnap->isChecked();
   ui.glcanvas->setGridSnapData( viewGrid, isSnapOn, sdx.toDouble(), sdy.toDouble() );
  }
  else
  {
   ui.actionGrid->setChecked( false );
  }
 }
 else
 {
  // set info to deactivate grid and snap
  ui.glcanvas->setGridSnapData( viewGrid, isSnapOn, dx, dy  );
 }
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
MyApp::on_actionDelete_triggered()
{
 ui.glcanvas->delSelectedEntities();
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
MyApp::on_actionIntersect_triggered()
{
 ui.glcanvas->intersectTwoSelectedCurves();
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
MyApp::on_actionCreateRegion_triggered()
{
 ui.glcanvas->createRegion();
}
//-------------------------------------------------------------------------

//--------------------------------------------------------------------
void
MyApp::on_actionFit_triggered()
{
 ui.glcanvas->fitWorldToViewport();
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
MyApp::on_actionZoomIn_triggered()
{
 ui.glcanvas->zoomIn();
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
MyApp::on_actionZoomOut_triggered()
{
 ui.glcanvas->zoomOut();
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
MyApp::on_actionPanLeft_triggered()
{
 ui.glcanvas->panLeft();
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
MyApp::on_actionPanRight_triggered()
{
 ui.glcanvas->panRight();
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
MyApp::on_actionPanDown_triggered()
{
 ui.glcanvas->panDown();
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
MyApp::on_actionPanUp_triggered()
{
 ui.glcanvas->panUp();
}
//--------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
MyApp::on_actionBoundaryMesh_triggered()
{
 Ui::MeshBoundary dlg; 
 QDialog *dialog = new QDialog;
 dlg.setupUi(dialog);
 int nSdv = 1;
 m_model->getNumSubdivOfFirstSelectedCurve( &nSdv );
 QString s_nSdv;
 s_nSdv.setNum( nSdv );
 dlg.lineEditNumSubdiv->clear();
 dlg.lineEditNumSubdiv->insert( s_nSdv );
 if( dialog->exec() == QDialog::Accepted )
 {
  s_nSdv = dlg.lineEditNumSubdiv->text();
  nSdv = s_nSdv.toInt();
  m_model->setNumSubdivOfSelectedCurves( nSdv );
  ui.glcanvas->resetModelDisplay();
  // returns to the selection mode
  this->on_actionSelect_triggered();
 }
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void 
MyApp::on_actionDomainMesh_triggered()
{
 Ui::MeshDomain dlg; 
 QDialog *dialog = new QDialog;
 dlg.setupUi(dialog);
 if( dialog->exec() == QDialog::Accepted )
 {
  int meshGenType = 0;
  if( dlg.radioButtonBilinear->isChecked ())
  {
    meshGenType = MeshGenerator::TRANSFIN_BILINEAR;
  }
  else if( dlg.radioButtonTrilinear->isChecked ())
  {
     meshGenType = MeshGenerator::TRANSFIN_TRILINEAR;
  }
  else // if( dlg.radioButtonDelaunay->isChecked ())
  {
     meshGenType = MeshGenerator::DELAUNAY;
  }
  m_model->generateMeshSelectedRegions(meshGenType);
  ui.glcanvas->resetModelDisplay();
  // returns to the selection mode
  this->on_actionSelect_triggered();
 }
}
//-------------------------------------------------------------------------
