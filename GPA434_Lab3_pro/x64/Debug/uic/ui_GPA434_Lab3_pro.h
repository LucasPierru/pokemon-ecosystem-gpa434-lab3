/********************************************************************************
** Form generated from reading UI file 'GPA434_Lab3_pro.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPA434_LAB3_PRO_H
#define UI_GPA434_LAB3_PRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GPA434_Lab3_proClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GPA434_Lab3_proClass)
    {
        if (GPA434_Lab3_proClass->objectName().isEmpty())
            GPA434_Lab3_proClass->setObjectName(QString::fromUtf8("GPA434_Lab3_proClass"));
        GPA434_Lab3_proClass->resize(600, 400);
        menuBar = new QMenuBar(GPA434_Lab3_proClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        GPA434_Lab3_proClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GPA434_Lab3_proClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GPA434_Lab3_proClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(GPA434_Lab3_proClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        GPA434_Lab3_proClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GPA434_Lab3_proClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GPA434_Lab3_proClass->setStatusBar(statusBar);

        retranslateUi(GPA434_Lab3_proClass);

        QMetaObject::connectSlotsByName(GPA434_Lab3_proClass);
    } // setupUi

    void retranslateUi(QMainWindow *GPA434_Lab3_proClass)
    {
        GPA434_Lab3_proClass->setWindowTitle(QCoreApplication::translate("GPA434_Lab3_proClass", "GPA434_Lab3_pro", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GPA434_Lab3_proClass: public Ui_GPA434_Lab3_proClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPA434_LAB3_PRO_H
