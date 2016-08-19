/********************************************************************************
** Form generated from reading UI file 'vtkshower.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VTKSHOWER_H
#define UI_VTKSHOWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_vtkShowerClass
{
public:
    QAction *action_k;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVTKWidget *qvtkWidget;
    QWidget *right_widget;
    QVBoxLayout *right;
    QRadioButton *radioButton_solid;
    QRadioButton *radioButton_wareline;
    QRadioButton *radioButton_setnode;
    QRadioButton *radioButton_setSeg;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_doc;
    QComboBox *comboBox;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *vtkShowerClass)
    {
        if (vtkShowerClass->objectName().isEmpty())
            vtkShowerClass->setObjectName(QStringLiteral("vtkShowerClass"));
        vtkShowerClass->resize(650, 515);
        action_k = new QAction(vtkShowerClass);
        action_k->setObjectName(QStringLiteral("action_k"));
        centralWidget = new QWidget(vtkShowerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 611, 361));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        qvtkWidget = new QVTKWidget(horizontalLayoutWidget);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));

        horizontalLayout->addWidget(qvtkWidget);

        right_widget = new QWidget(horizontalLayoutWidget);
        right_widget->setObjectName(QStringLiteral("right_widget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(right_widget->sizePolicy().hasHeightForWidth());
        right_widget->setSizePolicy(sizePolicy);
        right_widget->setMinimumSize(QSize(150, 0));
        right_widget->setMaximumSize(QSize(150, 16777215));
        right = new QVBoxLayout(right_widget);
        right->setSpacing(6);
        right->setContentsMargins(11, 11, 11, 11);
        right->setObjectName(QStringLiteral("right"));
        right->setSizeConstraint(QLayout::SetFixedSize);
        right->setContentsMargins(1, -1, -1, -1);
        radioButton_solid = new QRadioButton(right_widget);
        radioButton_solid->setObjectName(QStringLiteral("radioButton_solid"));
        sizePolicy.setHeightForWidth(radioButton_solid->sizePolicy().hasHeightForWidth());
        radioButton_solid->setSizePolicy(sizePolicy);
        radioButton_solid->setMinimumSize(QSize(150, 0));
        radioButton_solid->setMaximumSize(QSize(150, 16777215));
        radioButton_solid->setChecked(true);

        right->addWidget(radioButton_solid);

        radioButton_wareline = new QRadioButton(right_widget);
        radioButton_wareline->setObjectName(QStringLiteral("radioButton_wareline"));

        right->addWidget(radioButton_wareline);

        radioButton_setnode = new QRadioButton(right_widget);
        radioButton_setnode->setObjectName(QStringLiteral("radioButton_setnode"));

        right->addWidget(radioButton_setnode);

        radioButton_setSeg = new QRadioButton(right_widget);
        radioButton_setSeg->setObjectName(QStringLiteral("radioButton_setSeg"));

        right->addWidget(radioButton_setSeg);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_doc = new QLabel(right_widget);
        label_doc->setObjectName(QStringLiteral("label_doc"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_doc->sizePolicy().hasHeightForWidth());
        label_doc->setSizePolicy(sizePolicy1);
        label_doc->setMinimumSize(QSize(80, 0));
        label_doc->setMaximumSize(QSize(80, 20));

        horizontalLayout_2->addWidget(label_doc);

        comboBox = new QComboBox(right_widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(comboBox);


        right->addLayout(horizontalLayout_2);


        horizontalLayout->addWidget(right_widget, 0, Qt::AlignTop);

        vtkShowerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(vtkShowerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 650, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        vtkShowerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(vtkShowerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        vtkShowerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(vtkShowerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        vtkShowerClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());

        retranslateUi(vtkShowerClass);

        QMetaObject::connectSlotsByName(vtkShowerClass);
    } // setupUi

    void retranslateUi(QMainWindow *vtkShowerClass)
    {
        vtkShowerClass->setWindowTitle(QApplication::translate("vtkShowerClass", "vtkShower", 0));
        action_k->setText(QApplication::translate("vtkShowerClass", "\346\211\223\345\274\200k\346\226\207\344\273\266", 0));
        radioButton_solid->setText(QApplication::translate("vtkShowerClass", "\345\256\236\344\275\223\345\215\225\345\205\203", 0));
        radioButton_wareline->setText(QApplication::translate("vtkShowerClass", "\347\272\277\346\241\206\345\215\225\345\205\203", 0));
        radioButton_setnode->setText(QApplication::translate("vtkShowerClass", "\350\212\202\347\202\271\351\233\206\345\220\210", 0));
        radioButton_setSeg->setText(QApplication::translate("vtkShowerClass", "\350\212\202\347\202\271\351\235\242\351\233\206\345\220\210", 0));
        label_doc->setText(QApplication::translate("vtkShowerClass", "\344\275\223\347\274\226\345\217\267\357\274\232", 0));
        menu->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class vtkShowerClass: public Ui_vtkShowerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VTKSHOWER_H
