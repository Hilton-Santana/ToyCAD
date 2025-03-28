/********************************************************************************
** Form generated from reading UI file 'meshface.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESHFACE_H
#define UI_MESHFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeshDomain
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *buttonOK;
    QPushButton *buttonCancel;
    QLabel *labelMain;
    QRadioButton *radioButtonTrilinear;
    QRadioButton *radioButtonBilinear;
    QRadioButton *radioButtonDelaunay;

    void setupUi(QDialog *MeshDomain)
    {
        if (MeshDomain->objectName().isEmpty())
            MeshDomain->setObjectName(QStringLiteral("MeshDomain"));
        MeshDomain->resize(218, 182);
        layoutWidget = new QWidget(MeshDomain);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 140, 161, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        buttonOK = new QPushButton(layoutWidget);
        buttonOK->setObjectName(QStringLiteral("buttonOK"));

        hboxLayout->addWidget(buttonOK);

        buttonCancel = new QPushButton(layoutWidget);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));

        hboxLayout->addWidget(buttonCancel);

        labelMain = new QLabel(MeshDomain);
        labelMain->setObjectName(QStringLiteral("labelMain"));
        labelMain->setGeometry(QRect(30, 20, 91, 16));
        QFont font;
        font.setPointSize(10);
        labelMain->setFont(font);
        radioButtonTrilinear = new QRadioButton(MeshDomain);
        radioButtonTrilinear->setObjectName(QStringLiteral("radioButtonTrilinear"));
        radioButtonTrilinear->setGeometry(QRect(30, 80, 131, 17));
        radioButtonTrilinear->setFont(font);
        radioButtonTrilinear->setChecked(false);
        radioButtonBilinear = new QRadioButton(MeshDomain);
        radioButtonBilinear->setObjectName(QStringLiteral("radioButtonBilinear"));
        radioButtonBilinear->setGeometry(QRect(30, 50, 131, 17));
        radioButtonBilinear->setFont(font);
        radioButtonBilinear->setChecked(true);
        radioButtonDelaunay = new QRadioButton(MeshDomain);
        radioButtonDelaunay->setObjectName(QStringLiteral("radioButtonDelaunay"));
        radioButtonDelaunay->setGeometry(QRect(30, 110, 151, 17));
        radioButtonDelaunay->setFont(font);
        radioButtonDelaunay->setChecked(false);

        retranslateUi(MeshDomain);
        QObject::connect(buttonOK, SIGNAL(clicked()), MeshDomain, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), MeshDomain, SLOT(reject()));

        QMetaObject::connectSlotsByName(MeshDomain);
    } // setupUi

    void retranslateUi(QDialog *MeshDomain)
    {
        MeshDomain->setWindowTitle(QApplication::translate("MeshDomain", "Domain Meshing", 0));
        buttonOK->setText(QApplication::translate("MeshDomain", "OK", 0));
        buttonCancel->setText(QApplication::translate("MeshDomain", "Cancel", 0));
        labelMain->setText(QApplication::translate("MeshDomain", "Mesh Generator:", 0));
        radioButtonTrilinear->setText(QApplication::translate("MeshDomain", "Trilinear Mapping", 0));
        radioButtonBilinear->setText(QApplication::translate("MeshDomain", "Biilinear Mapping", 0));
        radioButtonDelaunay->setText(QApplication::translate("MeshDomain", "Delaunay Triangulation", 0));
    } // retranslateUi

};

namespace Ui {
    class MeshDomain: public Ui_MeshDomain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHFACE_H
