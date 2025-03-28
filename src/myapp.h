#ifndef MYAPP_H
#define MYAPP_H

#include <QtWidgets/QMainWindow>
#include "ui_myapp.h"
#include "ui_snapgrid.h"
#include "ui_meshedge.h"
#include "ui_meshface.h"
#include "mymodel.h"

class MyApp : public QMainWindow
{
	Q_OBJECT

public:
	MyApp(QWidget *parent = 0);
	~MyApp();

private slots:
	void on_actionSelect_triggered();
	void on_actionGrid_triggered();
	void on_actionLine_triggered();
	void on_actionPolyLine_triggered();
	void on_actionQuadBezier_triggered();
	void on_actionCubicBezier_triggered();
	void on_actionCircle_triggered();
	void on_actionCircleArc_triggered();
	void on_actionDelete_triggered();
	void on_actionIntersect_triggered();
	void on_actionCreateRegion_triggered();
	void on_actionFit_triggered();
	void on_actionZoomIn_triggered();
	void on_actionZoomOut_triggered();
	void on_actionPanLeft_triggered();
	void on_actionPanRight_triggered();
	void on_actionPanDown_triggered();
	void on_actionPanUp_triggered();
    void on_actionBoundaryMesh_triggered();
    void on_actionDomainMesh_triggered();

private:
	Ui::MyAppClass ui;
	Ui::GridDialog m_gridDlg; 
	QDialog* m_gridDialog;
	MyModel* m_model;
};

#endif // MYAPP_H
