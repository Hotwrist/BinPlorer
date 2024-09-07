/********************************************************************************
** Form generated from reading UI file 'binplorer.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BINPLORER_H
#define UI_BINPLORER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BinPlorer
{
public:
    QAction *actionAbout_BinPlorer;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QTableWidget *tableWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *BinPlorer)
    {
        if (BinPlorer->objectName().isEmpty())
            BinPlorer->setObjectName("BinPlorer");
        BinPlorer->resize(630, 502);
        actionAbout_BinPlorer = new QAction(BinPlorer);
        actionAbout_BinPlorer->setObjectName("actionAbout_BinPlorer");
        centralwidget = new QWidget(BinPlorer);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");

        horizontalLayout->addWidget(tableWidget);

        tableWidget_2 = new QTableWidget(centralwidget);
        tableWidget_2->setObjectName("tableWidget_2");

        horizontalLayout->addWidget(tableWidget_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(188, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(168, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        BinPlorer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BinPlorer);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 630, 27));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        BinPlorer->setMenuBar(menubar);
        statusbar = new QStatusBar(BinPlorer);
        statusbar->setObjectName("statusbar");
        BinPlorer->setStatusBar(statusbar);
        toolBar = new QToolBar(BinPlorer);
        toolBar->setObjectName("toolBar");
        BinPlorer->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout_BinPlorer);

        retranslateUi(BinPlorer);

        QMetaObject::connectSlotsByName(BinPlorer);
    } // setupUi

    void retranslateUi(QMainWindow *BinPlorer)
    {
        BinPlorer->setWindowTitle(QCoreApplication::translate("BinPlorer", "BinPlorer", nullptr));
        actionAbout_BinPlorer->setText(QCoreApplication::translate("BinPlorer", "About BinPlorer", nullptr));
        label->setText(QCoreApplication::translate("BinPlorer", "File Info:", nullptr));
        pushButton->setText(QCoreApplication::translate("BinPlorer", "Open Binary File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("BinPlorer", "Help", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("BinPlorer", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BinPlorer: public Ui_BinPlorer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BINPLORER_H
