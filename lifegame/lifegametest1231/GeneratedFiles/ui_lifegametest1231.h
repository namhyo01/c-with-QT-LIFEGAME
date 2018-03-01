/********************************************************************************
** Form generated from reading UI file 'lifegametest1231.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIFEGAMETEST1231_H
#define UI_LIFEGAMETEST1231_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lifegametest1231Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *lifegametest1231Class)
    {
        if (lifegametest1231Class->objectName().isEmpty())
            lifegametest1231Class->setObjectName(QStringLiteral("lifegametest1231Class"));
        lifegametest1231Class->resize(600, 400);
        menuBar = new QMenuBar(lifegametest1231Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        lifegametest1231Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(lifegametest1231Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        lifegametest1231Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(lifegametest1231Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lifegametest1231Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(lifegametest1231Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        lifegametest1231Class->setStatusBar(statusBar);

        retranslateUi(lifegametest1231Class);

        QMetaObject::connectSlotsByName(lifegametest1231Class);
    } // setupUi

    void retranslateUi(QMainWindow *lifegametest1231Class)
    {
        lifegametest1231Class->setWindowTitle(QApplication::translate("lifegametest1231Class", "lifegametest1231", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class lifegametest1231Class: public Ui_lifegametest1231Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIFEGAMETEST1231_H
