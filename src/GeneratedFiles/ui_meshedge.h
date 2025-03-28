/********************************************************************************
** Form generated from reading UI file 'meshedge.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESHEDGE_H
#define UI_MESHEDGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeshBoundary
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *buttonOK;
    QPushButton *buttonCancel;
    QLineEdit *lineEditNumSubdiv;
    QLabel *labelSubdiv;

    void setupUi(QDialog *MeshBoundary)
    {
        if (MeshBoundary->objectName().isEmpty())
            MeshBoundary->setObjectName(QStringLiteral("MeshBoundary"));
        MeshBoundary->setEnabled(true);
        MeshBoundary->resize(211, 182);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MeshBoundary->sizePolicy().hasHeightForWidth());
        MeshBoundary->setSizePolicy(sizePolicy);
        MeshBoundary->setMinimumSize(QSize(211, 182));
        MeshBoundary->setMaximumSize(QSize(211, 182));
        MeshBoundary->setSizeGripEnabled(false);
        layoutWidget = new QWidget(MeshBoundary);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 120, 171, 33));
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

        lineEditNumSubdiv = new QLineEdit(MeshBoundary);
        lineEditNumSubdiv->setObjectName(QStringLiteral("lineEditNumSubdiv"));
        lineEditNumSubdiv->setGeometry(QRect(120, 40, 51, 21));
        QFont font;
        font.setPointSize(10);
        lineEditNumSubdiv->setFont(font);
        lineEditNumSubdiv->setAlignment(Qt::AlignCenter);
        labelSubdiv = new QLabel(MeshBoundary);
        labelSubdiv->setObjectName(QStringLiteral("labelSubdiv"));
        labelSubdiv->setGeometry(QRect(30, 40, 81, 21));
        labelSubdiv->setFont(font);

        retranslateUi(MeshBoundary);
        QObject::connect(buttonOK, SIGNAL(clicked()), MeshBoundary, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), MeshBoundary, SLOT(reject()));

        QMetaObject::connectSlotsByName(MeshBoundary);
    } // setupUi

    void retranslateUi(QDialog *MeshBoundary)
    {
        MeshBoundary->setWindowTitle(QApplication::translate("MeshBoundary", "Boundary Meshing", 0));
        buttonOK->setText(QApplication::translate("MeshBoundary", "OK", 0));
        buttonCancel->setText(QApplication::translate("MeshBoundary", "Cancel", 0));
#ifndef QT_NO_ACCESSIBILITY
        lineEditNumSubdiv->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        lineEditNumSubdiv->setText(QApplication::translate("MeshBoundary", "1", 0));
        labelSubdiv->setText(QApplication::translate("MeshBoundary", "Subdivisions =", 0));
    } // retranslateUi

};

namespace Ui {
    class MeshBoundary: public Ui_MeshBoundary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHEDGE_H
