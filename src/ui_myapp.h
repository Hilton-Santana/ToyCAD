/********************************************************************************
** Form generated from reading UI file 'myapp.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYAPP_H
#define UI_MYAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "glcanvas.h"

QT_BEGIN_NAMESPACE

class Ui_MyAppClass
{
public:
    QAction *actionFit;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionPanLeft;
    QAction *actionPanRight;
    QAction *actionPanDown;
    QAction *actionPanUp;
    QAction *actionSelect;
    QAction *actionLine;
    QAction *actionDelete;
    QAction *actionGrid;
    QAction *actionIntersect;
    QAction *actionCreateRegion;
    QAction *actionBoundaryMesh;
    QAction *actionDomainMesh;
    QAction *actionPolyLine;
    QAction *actionQuadBezier;
    QAction *actionCubicBezier;
    QAction *actionCircle;
    QAction *actionCircleArc;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    GLCanvas *glcanvas;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *modelingToolBar;
    QToolBar *meshToolBar;

    void setupUi(QMainWindow *MyAppClass)
    {
        if (MyAppClass->objectName().isEmpty())
            MyAppClass->setObjectName(QStringLiteral("MyAppClass"));
        MyAppClass->resize(600, 400);
        actionFit = new QAction(MyAppClass);
        actionFit->setObjectName(QStringLiteral("actionFit"));
        QIcon icon;
        icon.addFile(QStringLiteral("icons/fit.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionFit->setIcon(icon);
        actionZoomIn = new QAction(MyAppClass);
        actionZoomIn->setObjectName(QStringLiteral("actionZoomIn"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("icons/zoomIn2.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomIn->setIcon(icon1);
        actionZoomOut = new QAction(MyAppClass);
        actionZoomOut->setObjectName(QStringLiteral("actionZoomOut"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("icons/zoomout2.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomOut->setIcon(icon2);
        actionPanLeft = new QAction(MyAppClass);
        actionPanLeft->setObjectName(QStringLiteral("actionPanLeft"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("icons/arrowLeft2.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPanLeft->setIcon(icon3);
        actionPanRight = new QAction(MyAppClass);
        actionPanRight->setObjectName(QStringLiteral("actionPanRight"));
        QIcon icon4;
        icon4.addFile(QStringLiteral("icons/arrowrRight.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPanRight->setIcon(icon4);
        actionPanDown = new QAction(MyAppClass);
        actionPanDown->setObjectName(QStringLiteral("actionPanDown"));
        QIcon icon5;
        icon5.addFile(QStringLiteral("icons/arrowrDown.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPanDown->setIcon(icon5);
        actionPanUp = new QAction(MyAppClass);
        actionPanUp->setObjectName(QStringLiteral("actionPanUp"));
        QIcon icon6;
        icon6.addFile(QStringLiteral("icons/arrowup2.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPanUp->setIcon(icon6);
        actionSelect = new QAction(MyAppClass);
        actionSelect->setObjectName(QStringLiteral("actionSelect"));
        actionSelect->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QStringLiteral("icons/mouse3.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect->setIcon(icon7);
        actionLine = new QAction(MyAppClass);
        actionLine->setObjectName(QStringLiteral("actionLine"));
        actionLine->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral("icons/line.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLine->setIcon(icon8);
        actionDelete = new QAction(MyAppClass);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        QIcon icon9;
        icon9.addFile(QStringLiteral("icons/delete3.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon9);
        actionGrid = new QAction(MyAppClass);
        actionGrid->setObjectName(QStringLiteral("actionGrid"));
        actionGrid->setCheckable(true);
        QIcon icon10;
        icon10.addFile(QStringLiteral("icons/grid2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGrid->setIcon(icon10);
        actionIntersect = new QAction(MyAppClass);
        actionIntersect->setObjectName(QStringLiteral("actionIntersect"));
        QIcon icon11;
        icon11.addFile(QStringLiteral("icons/intersect2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionIntersect->setIcon(icon11);
        actionCreateRegion = new QAction(MyAppClass);
        actionCreateRegion->setObjectName(QStringLiteral("actionCreateRegion"));
        QIcon icon12;
        icon12.addFile(QStringLiteral("icons/region.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreateRegion->setIcon(icon12);
        actionBoundaryMesh = new QAction(MyAppClass);
        actionBoundaryMesh->setObjectName(QStringLiteral("actionBoundaryMesh"));
        QIcon icon13;
        icon13.addFile(QStringLiteral("icons/boundarymesh2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBoundaryMesh->setIcon(icon13);
        actionDomainMesh = new QAction(MyAppClass);
        actionDomainMesh->setObjectName(QStringLiteral("actionDomainMesh"));
        QIcon icon14;
        icon14.addFile(QStringLiteral("icons/mesh.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDomainMesh->setIcon(icon14);
        actionPolyLine = new QAction(MyAppClass);
        actionPolyLine->setObjectName(QStringLiteral("actionPolyLine"));
        actionPolyLine->setCheckable(true);
        QIcon icon15;
        icon15.addFile(QStringLiteral("icons/poly2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPolyLine->setIcon(icon15);
        actionQuadBezier = new QAction(MyAppClass);
        actionQuadBezier->setObjectName(QStringLiteral("actionQuadBezier"));
        actionQuadBezier->setCheckable(true);
        QIcon icon16;
        icon16.addFile(QStringLiteral("icons/quadbezier.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuadBezier->setIcon(icon16);
        actionCubicBezier = new QAction(MyAppClass);
        actionCubicBezier->setObjectName(QStringLiteral("actionCubicBezier"));
        actionCubicBezier->setCheckable(true);
        QIcon icon17;
        icon17.addFile(QStringLiteral("icons/cubicbezier2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCubicBezier->setIcon(icon17);
        actionCircle = new QAction(MyAppClass);
        actionCircle->setObjectName(QStringLiteral("actionCircle"));
        actionCircle->setCheckable(true);
        QIcon icon18;
        icon18.addFile(QStringLiteral("icons/circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCircle->setIcon(icon18);
        actionCircleArc = new QAction(MyAppClass);
        actionCircleArc->setObjectName(QStringLiteral("actionCircleArc"));
        actionCircleArc->setCheckable(true);
        QIcon icon19;
        icon19.addFile(QStringLiteral("icons/circlearc.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCircleArc->setIcon(icon19);
        centralWidget = new QWidget(MyAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        glcanvas = new GLCanvas(centralWidget);
        glcanvas->setObjectName(QStringLiteral("glcanvas"));

        horizontalLayout->addWidget(glcanvas);

        MyAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        MyAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyAppClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyAppClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MyAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyAppClass->setStatusBar(statusBar);
        modelingToolBar = new QToolBar(MyAppClass);
        modelingToolBar->setObjectName(QStringLiteral("modelingToolBar"));
        MyAppClass->addToolBar(Qt::TopToolBarArea, modelingToolBar);
        MyAppClass->insertToolBarBreak(modelingToolBar);
        meshToolBar = new QToolBar(MyAppClass);
        meshToolBar->setObjectName(QStringLiteral("meshToolBar"));
        MyAppClass->addToolBar(Qt::TopToolBarArea, meshToolBar);
        MyAppClass->insertToolBarBreak(meshToolBar);

        mainToolBar->addAction(actionFit);
        mainToolBar->addAction(actionZoomIn);
        mainToolBar->addAction(actionZoomOut);
        mainToolBar->addAction(actionPanLeft);
        mainToolBar->addAction(actionPanRight);
        mainToolBar->addAction(actionPanDown);
        mainToolBar->addAction(actionPanUp);
        modelingToolBar->addAction(actionSelect);
        modelingToolBar->addAction(actionGrid);
        modelingToolBar->addSeparator();
        modelingToolBar->addAction(actionLine);
        modelingToolBar->addSeparator();
        modelingToolBar->addAction(actionPolyLine);
        modelingToolBar->addAction(actionQuadBezier);
        modelingToolBar->addAction(actionCubicBezier);
        modelingToolBar->addAction(actionCircle);
        modelingToolBar->addAction(actionCircleArc);
        modelingToolBar->addAction(actionDelete);
        modelingToolBar->addAction(actionIntersect);
        modelingToolBar->addAction(actionCreateRegion);
        meshToolBar->addAction(actionBoundaryMesh);
        meshToolBar->addAction(actionDomainMesh);

        retranslateUi(MyAppClass);

        QMetaObject::connectSlotsByName(MyAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyAppClass)
    {
        MyAppClass->setWindowTitle(QApplication::translate("MyAppClass", "ToyCAD", 0));
        actionFit->setText(QApplication::translate("MyAppClass", "Fit", 0));
#ifndef QT_NO_TOOLTIP
        actionFit->setToolTip(QApplication::translate("MyAppClass", "Adjust object image to fit on canvas", 0));
#endif // QT_NO_TOOLTIP
        actionZoomIn->setText(QApplication::translate("MyAppClass", "ZoomIn", 0));
#ifndef QT_NO_TOOLTIP
        actionZoomIn->setToolTip(QApplication::translate("MyAppClass", "Zoom in object image on canvas", 0));
#endif // QT_NO_TOOLTIP
        actionZoomOut->setText(QApplication::translate("MyAppClass", "ZoomOut", 0));
#ifndef QT_NO_TOOLTIP
        actionZoomOut->setToolTip(QApplication::translate("MyAppClass", "Zoom out object image on canvas", 0));
#endif // QT_NO_TOOLTIP
        actionPanLeft->setText(QApplication::translate("MyAppClass", "PanLeft", 0));
#ifndef QT_NO_TOOLTIP
        actionPanLeft->setToolTip(QApplication::translate("MyAppClass", "Translate left object image on canvas", 0));
#endif // QT_NO_TOOLTIP
        actionPanRight->setText(QApplication::translate("MyAppClass", "PanRight", 0));
#ifndef QT_NO_TOOLTIP
        actionPanRight->setToolTip(QApplication::translate("MyAppClass", "Translate right object image on canvas", 0));
#endif // QT_NO_TOOLTIP
        actionPanDown->setText(QApplication::translate("MyAppClass", "PanDown", 0));
#ifndef QT_NO_TOOLTIP
        actionPanDown->setToolTip(QApplication::translate("MyAppClass", "Translate down object image on canvas", 0));
#endif // QT_NO_TOOLTIP
        actionPanUp->setText(QApplication::translate("MyAppClass", "PanUp", 0));
#ifndef QT_NO_TOOLTIP
        actionPanUp->setToolTip(QApplication::translate("MyAppClass", "Translate up object image on canvas", 0));
#endif // QT_NO_TOOLTIP
        actionSelect->setText(QApplication::translate("MyAppClass", "Select", 0));
#ifndef QT_NO_TOOLTIP
        actionSelect->setToolTip(QApplication::translate("MyAppClass", "Set selection mode", 0));
#endif // QT_NO_TOOLTIP
        actionLine->setText(QApplication::translate("MyAppClass", "Line", 0));
#ifndef QT_NO_TOOLTIP
        actionLine->setToolTip(QApplication::translate("MyAppClass", "Insert a straight line segment", 0));
#endif // QT_NO_TOOLTIP
        actionDelete->setText(QApplication::translate("MyAppClass", "Delete", 0));
#ifndef QT_NO_TOOLTIP
        actionDelete->setToolTip(QApplication::translate("MyAppClass", "Delete selected entities", 0));
#endif // QT_NO_TOOLTIP
        actionGrid->setText(QApplication::translate("MyAppClass", "Grid", 0));
#ifndef QT_NO_TOOLTIP
        actionGrid->setToolTip(QApplication::translate("MyAppClass", "Specity grid points", 0));
#endif // QT_NO_TOOLTIP
        actionIntersect->setText(QApplication::translate("MyAppClass", "Intersect", 0));
#ifndef QT_NO_TOOLTIP
        actionIntersect->setToolTip(QApplication::translate("MyAppClass", "Intersect two selected curves", 0));
#endif // QT_NO_TOOLTIP
        actionCreateRegion->setText(QApplication::translate("MyAppClass", "CreateRegion", 0));
#ifndef QT_NO_TOOLTIP
        actionCreateRegion->setToolTip(QApplication::translate("MyAppClass", "Create region from selected curves", 0));
#endif // QT_NO_TOOLTIP
        actionBoundaryMesh->setText(QApplication::translate("MyAppClass", "BoundaryMesh", 0));
#ifndef QT_NO_TOOLTIP
        actionBoundaryMesh->setToolTip(QApplication::translate("MyAppClass", "Specify curve number of subdivisions", 0));
#endif // QT_NO_TOOLTIP
        actionDomainMesh->setText(QApplication::translate("MyAppClass", "DomainMesh", 0));
#ifndef QT_NO_TOOLTIP
        actionDomainMesh->setToolTip(QApplication::translate("MyAppClass", "Generate mesh in region", 0));
#endif // QT_NO_TOOLTIP
        actionPolyLine->setText(QApplication::translate("MyAppClass", "PolyLine", 0));
#ifndef QT_NO_TOOLTIP
        actionPolyLine->setToolTip(QApplication::translate("MyAppClass", "Insert a polyline", 0));
#endif // QT_NO_TOOLTIP
        actionQuadBezier->setText(QApplication::translate("MyAppClass", "QuadBezier", 0));
#ifndef QT_NO_TOOLTIP
        actionQuadBezier->setToolTip(QApplication::translate("MyAppClass", "Insert a quadbezier", 0));
#endif // QT_NO_TOOLTIP
        actionCubicBezier->setText(QApplication::translate("MyAppClass", "CubicBezier", 0));
#ifndef QT_NO_TOOLTIP
        actionCubicBezier->setToolTip(QApplication::translate("MyAppClass", "Insert a cubicbezier", 0));
#endif // QT_NO_TOOLTIP
        actionCircle->setText(QApplication::translate("MyAppClass", "Circle", 0));
#ifndef QT_NO_TOOLTIP
        actionCircle->setToolTip(QApplication::translate("MyAppClass", "Insert a circle", 0));
#endif // QT_NO_TOOLTIP
        actionCircleArc->setText(QApplication::translate("MyAppClass", "CircleArc", 0));
#ifndef QT_NO_TOOLTIP
        actionCircleArc->setToolTip(QApplication::translate("MyAppClass", "Insert a circle arc", 0));
#endif // QT_NO_TOOLTIP
        modelingToolBar->setWindowTitle(QApplication::translate("MyAppClass", "toolBar", 0));
        meshToolBar->setWindowTitle(QApplication::translate("MyAppClass", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MyAppClass: public Ui_MyAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYAPP_H
