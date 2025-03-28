/********************************************************************************
** Form generated from reading UI file 'snapgrid.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNAPGRID_H
#define UI_SNAPGRID_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GridDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *okButton;
    QPushButton *buttonCancel;
    QLineEdit *lineEditXdir;
    QLabel *labelMain;
    QLabel *labelXdir;
    QLabel *labelYdir;
    QLineEdit *lineEditYdir;
    QCheckBox *checkBoxSnap;

    void setupUi(QDialog *GridDialog)
    {
        if (GridDialog->objectName().isEmpty())
            GridDialog->setObjectName(QStringLiteral("GridDialog"));
        GridDialog->resize(171, 209);
        GridDialog->setMinimumSize(QSize(171, 209));
        GridDialog->setMaximumSize(QSize(171, 209));
        layoutWidget = new QWidget(GridDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 160, 158, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        buttonCancel = new QPushButton(layoutWidget);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));

        hboxLayout->addWidget(buttonCancel);

        lineEditXdir = new QLineEdit(GridDialog);
        lineEditXdir->setObjectName(QStringLiteral("lineEditXdir"));
        lineEditXdir->setGeometry(QRect(70, 50, 61, 21));
        QFont font;
        font.setPointSize(10);
        lineEditXdir->setFont(font);
        labelMain = new QLabel(GridDialog);
        labelMain->setObjectName(QStringLiteral("labelMain"));
        labelMain->setGeometry(QRect(40, 20, 91, 16));
        labelMain->setFont(font);
        labelXdir = new QLabel(GridDialog);
        labelXdir->setObjectName(QStringLiteral("labelXdir"));
        labelXdir->setGeometry(QRect(30, 50, 41, 21));
        QFont font1;
        font1.setPointSize(9);
        labelXdir->setFont(font1);
        labelYdir = new QLabel(GridDialog);
        labelYdir->setObjectName(QStringLiteral("labelYdir"));
        labelYdir->setGeometry(QRect(30, 80, 41, 21));
        labelYdir->setFont(font1);
        lineEditYdir = new QLineEdit(GridDialog);
        lineEditYdir->setObjectName(QStringLiteral("lineEditYdir"));
        lineEditYdir->setGeometry(QRect(70, 80, 61, 21));
        lineEditYdir->setFont(font);
        checkBoxSnap = new QCheckBox(GridDialog);
        checkBoxSnap->setObjectName(QStringLiteral("checkBoxSnap"));
        checkBoxSnap->setGeometry(QRect(40, 120, 91, 17));
        checkBoxSnap->setFont(font1);

        retranslateUi(GridDialog);
        QObject::connect(okButton, SIGNAL(clicked()), GridDialog, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), GridDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(GridDialog);
    } // setupUi

    void retranslateUi(QDialog *GridDialog)
    {
        GridDialog->setWindowTitle(QApplication::translate("GridDialog", "Grid/Snap", 0));
        okButton->setText(QApplication::translate("GridDialog", "OK", 0));
        buttonCancel->setText(QApplication::translate("GridDialog", "Cancel", 0));
        labelMain->setText(QApplication::translate("GridDialog", "Grid definition:", 0));
        labelXdir->setText(QApplication::translate("GridDialog", "x dir =", 0));
        labelYdir->setText(QApplication::translate("GridDialog", "y dir =", 0));
        checkBoxSnap->setText(QApplication::translate("GridDialog", "Snap to grid", 0));
    } // retranslateUi

};

namespace Ui {
    class GridDialog: public Ui_GridDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNAPGRID_H
