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
#include <QtWidgets/QPushButton>
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
    QAction *action;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *leftVerticalLayout;
    QVTKWidget *qvtkWidget;
    QWidget *playWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonPlay;
    QPushButton *pushButton_2;
    QWidget *right_widget_k;
    QVBoxLayout *right;
    QRadioButton *radioButton_solid;
    QRadioButton *radioButton_wareline;
    QRadioButton *radioButton_setnode;
    QRadioButton *radioButton_setSeg;
    QHBoxLayout *horizontalLayout_part;
    QLabel *label_doc;
    QComboBox *comboBox;
    QWidget *right_widget_lsd;
    QVBoxLayout *right_2;
    QRadioButton *radioButton_point_data;
    QRadioButton *radioButton_shell_data;
    QHBoxLayout *horizontalLayout_data;
    QLabel *label_doc_2;
    QComboBox *comboBox_data_name;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *vtkShowerClass)
    {
        if (vtkShowerClass->objectName().isEmpty())
            vtkShowerClass->setObjectName(QStringLiteral("vtkShowerClass"));
        vtkShowerClass->resize(650, 515);
        action = new QAction(vtkShowerClass);
        action->setObjectName(QStringLiteral("action"));
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
        leftVerticalLayout = new QVBoxLayout();
        leftVerticalLayout->setSpacing(6);
        leftVerticalLayout->setObjectName(QStringLiteral("leftVerticalLayout"));
        qvtkWidget = new QVTKWidget(horizontalLayoutWidget);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));

        leftVerticalLayout->addWidget(qvtkWidget);

        playWidget = new QWidget(horizontalLayoutWidget);
        playWidget->setObjectName(QStringLiteral("playWidget"));
        horizontalLayout_3 = new QHBoxLayout(playWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButtonPlay = new QPushButton(playWidget);
        pushButtonPlay->setObjectName(QStringLiteral("pushButtonPlay"));

        horizontalLayout_3->addWidget(pushButtonPlay);

        pushButton_2 = new QPushButton(playWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);


        leftVerticalLayout->addWidget(playWidget);


        horizontalLayout->addLayout(leftVerticalLayout);

        right_widget_k = new QWidget(horizontalLayoutWidget);
        right_widget_k->setObjectName(QStringLiteral("right_widget_k"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(right_widget_k->sizePolicy().hasHeightForWidth());
        right_widget_k->setSizePolicy(sizePolicy);
        right_widget_k->setMinimumSize(QSize(150, 0));
        right_widget_k->setMaximumSize(QSize(150, 16777215));
        right = new QVBoxLayout(right_widget_k);
        right->setSpacing(6);
        right->setContentsMargins(11, 11, 11, 11);
        right->setObjectName(QStringLiteral("right"));
        right->setSizeConstraint(QLayout::SetFixedSize);
        right->setContentsMargins(1, -1, -1, -1);
        radioButton_solid = new QRadioButton(right_widget_k);
        radioButton_solid->setObjectName(QStringLiteral("radioButton_solid"));
        sizePolicy.setHeightForWidth(radioButton_solid->sizePolicy().hasHeightForWidth());
        radioButton_solid->setSizePolicy(sizePolicy);
        radioButton_solid->setMinimumSize(QSize(150, 0));
        radioButton_solid->setMaximumSize(QSize(150, 16777215));
        radioButton_solid->setChecked(true);

        right->addWidget(radioButton_solid);

        radioButton_wareline = new QRadioButton(right_widget_k);
        radioButton_wareline->setObjectName(QStringLiteral("radioButton_wareline"));

        right->addWidget(radioButton_wareline);

        radioButton_setnode = new QRadioButton(right_widget_k);
        radioButton_setnode->setObjectName(QStringLiteral("radioButton_setnode"));

        right->addWidget(radioButton_setnode);

        radioButton_setSeg = new QRadioButton(right_widget_k);
        radioButton_setSeg->setObjectName(QStringLiteral("radioButton_setSeg"));

        right->addWidget(radioButton_setSeg);

        horizontalLayout_part = new QHBoxLayout();
        horizontalLayout_part->setSpacing(6);
        horizontalLayout_part->setObjectName(QStringLiteral("horizontalLayout_part"));
        label_doc = new QLabel(right_widget_k);
        label_doc->setObjectName(QStringLiteral("label_doc"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_doc->sizePolicy().hasHeightForWidth());
        label_doc->setSizePolicy(sizePolicy1);
        label_doc->setMinimumSize(QSize(80, 0));
        label_doc->setMaximumSize(QSize(80, 20));

        horizontalLayout_part->addWidget(label_doc);

        comboBox = new QComboBox(right_widget_k);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy2);

        horizontalLayout_part->addWidget(comboBox);


        right->addLayout(horizontalLayout_part);


        horizontalLayout->addWidget(right_widget_k, 0, Qt::AlignTop);

        right_widget_lsd = new QWidget(horizontalLayoutWidget);
        right_widget_lsd->setObjectName(QStringLiteral("right_widget_lsd"));
        sizePolicy.setHeightForWidth(right_widget_lsd->sizePolicy().hasHeightForWidth());
        right_widget_lsd->setSizePolicy(sizePolicy);
        right_widget_lsd->setMinimumSize(QSize(150, 0));
        right_widget_lsd->setMaximumSize(QSize(150, 16777215));
        right_2 = new QVBoxLayout(right_widget_lsd);
        right_2->setSpacing(6);
        right_2->setContentsMargins(11, 11, 11, 11);
        right_2->setObjectName(QStringLiteral("right_2"));
        right_2->setSizeConstraint(QLayout::SetFixedSize);
        right_2->setContentsMargins(1, -1, -1, -1);
        radioButton_point_data = new QRadioButton(right_widget_lsd);
        radioButton_point_data->setObjectName(QStringLiteral("radioButton_point_data"));
        sizePolicy.setHeightForWidth(radioButton_point_data->sizePolicy().hasHeightForWidth());
        radioButton_point_data->setSizePolicy(sizePolicy);
        radioButton_point_data->setMinimumSize(QSize(150, 0));
        radioButton_point_data->setMaximumSize(QSize(150, 16777215));
        radioButton_point_data->setChecked(true);

        right_2->addWidget(radioButton_point_data);

        radioButton_shell_data = new QRadioButton(right_widget_lsd);
        radioButton_shell_data->setObjectName(QStringLiteral("radioButton_shell_data"));

        right_2->addWidget(radioButton_shell_data);

        horizontalLayout_data = new QHBoxLayout();
        horizontalLayout_data->setSpacing(6);
        horizontalLayout_data->setObjectName(QStringLiteral("horizontalLayout_data"));
        label_doc_2 = new QLabel(right_widget_lsd);
        label_doc_2->setObjectName(QStringLiteral("label_doc_2"));
        sizePolicy1.setHeightForWidth(label_doc_2->sizePolicy().hasHeightForWidth());
        label_doc_2->setSizePolicy(sizePolicy1);
        label_doc_2->setMinimumSize(QSize(80, 0));
        label_doc_2->setMaximumSize(QSize(80, 20));

        horizontalLayout_data->addWidget(label_doc_2);

        comboBox_data_name = new QComboBox(right_widget_lsd);
        comboBox_data_name->setObjectName(QStringLiteral("comboBox_data_name"));
        sizePolicy2.setHeightForWidth(comboBox_data_name->sizePolicy().hasHeightForWidth());
        comboBox_data_name->setSizePolicy(sizePolicy2);

        horizontalLayout_data->addWidget(comboBox_data_name);


        right_2->addLayout(horizontalLayout_data);


        horizontalLayout->addWidget(right_widget_lsd);

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
        menu->addAction(action);

        retranslateUi(vtkShowerClass);

        QMetaObject::connectSlotsByName(vtkShowerClass);
    } // setupUi

    void retranslateUi(QMainWindow *vtkShowerClass)
    {
        vtkShowerClass->setWindowTitle(QApplication::translate("vtkShowerClass", "vtkShower", 0));
        action->setText(QApplication::translate("vtkShowerClass", "\346\211\223\345\274\200k\346\226\207\344\273\266", 0));
        pushButtonPlay->setText(QApplication::translate("vtkShowerClass", "\346\222\255\346\224\276", 0));
        pushButton_2->setText(QApplication::translate("vtkShowerClass", "\345\201\234\346\255\242", 0));
        radioButton_solid->setText(QApplication::translate("vtkShowerClass", "\345\256\236\344\275\223\345\215\225\345\205\203", 0));
        radioButton_wareline->setText(QApplication::translate("vtkShowerClass", "\347\272\277\346\241\206\345\215\225\345\205\203", 0));
        radioButton_setnode->setText(QApplication::translate("vtkShowerClass", "\350\212\202\347\202\271\351\233\206\345\220\210", 0));
        radioButton_setSeg->setText(QApplication::translate("vtkShowerClass", "\350\212\202\347\202\271\351\235\242\351\233\206\345\220\210", 0));
        label_doc->setText(QApplication::translate("vtkShowerClass", "\344\275\223\347\274\226\345\217\267\357\274\232", 0));
        radioButton_point_data->setText(QApplication::translate("vtkShowerClass", "\347\202\271\346\225\260\346\215\256", 0));
        radioButton_shell_data->setText(QApplication::translate("vtkShowerClass", "\345\243\263\346\225\260\346\215\256", 0));
        label_doc_2->setText(QApplication::translate("vtkShowerClass", "\346\225\260\346\215\256\345\220\215\347\247\260\357\274\232", 0));
        menu->setTitle(QApplication::translate("vtkShowerClass", "\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class vtkShowerClass: public Ui_vtkShowerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VTKSHOWER_H
