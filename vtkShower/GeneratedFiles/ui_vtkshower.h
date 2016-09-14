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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
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
    QAction *action_LSDyna;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *leftVerticalLayout;
    QVTKWidget *qvtkWidget;
    QWidget *playWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_play;
    QPushButton *pushButton_stop;
    QSlider *horizontalSlider_frame;
    QLabel *label_frame;
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
    QLabel *label_doc_4;
    QVBoxLayout *verticalLayout_part;
    QHBoxLayout *horizontalLayout_data;
    QLabel *label_doc_2;
    QComboBox *comboBox_data_name;
    QHBoxLayout *horizontalLayout_data_2;
    QLabel *label_doc_3;
    QComboBox *comboBox_data_color;
    QWidget *verticalWidget_range;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_min;
    QLabel *label;
    QLineEdit *lineEdit_min;
    QHBoxLayout *horizontalLayout_max;
    QLabel *label_2;
    QLineEdit *lineEdit_max;
    QPushButton *pushButton_range_change;
    QPushButton *pushButton_line;
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
        action_LSDyna = new QAction(vtkShowerClass);
        action_LSDyna->setObjectName(QStringLiteral("action_LSDyna"));
        centralWidget = new QWidget(vtkShowerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 592, 294));
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
        pushButton_play = new QPushButton(playWidget);
        pushButton_play->setObjectName(QStringLiteral("pushButton_play"));

        horizontalLayout_3->addWidget(pushButton_play);

        pushButton_stop = new QPushButton(playWidget);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));

        horizontalLayout_3->addWidget(pushButton_stop);

        horizontalSlider_frame = new QSlider(playWidget);
        horizontalSlider_frame->setObjectName(QStringLiteral("horizontalSlider_frame"));
        horizontalSlider_frame->setOrientation(Qt::Horizontal);
        horizontalSlider_frame->setTickPosition(QSlider::TicksBelow);

        horizontalLayout_3->addWidget(horizontalSlider_frame);

        label_frame = new QLabel(playWidget);
        label_frame->setObjectName(QStringLiteral("label_frame"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_frame->sizePolicy().hasHeightForWidth());
        label_frame->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_frame);


        leftVerticalLayout->addWidget(playWidget);


        horizontalLayout->addLayout(leftVerticalLayout);

        right_widget_k = new QWidget(horizontalLayoutWidget);
        right_widget_k->setObjectName(QStringLiteral("right_widget_k"));
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

        label_doc_4 = new QLabel(right_widget_lsd);
        label_doc_4->setObjectName(QStringLiteral("label_doc_4"));
        sizePolicy1.setHeightForWidth(label_doc_4->sizePolicy().hasHeightForWidth());
        label_doc_4->setSizePolicy(sizePolicy1);
        label_doc_4->setMinimumSize(QSize(80, 0));
        label_doc_4->setMaximumSize(QSize(80, 20));

        right_2->addWidget(label_doc_4);

        verticalLayout_part = new QVBoxLayout();
        verticalLayout_part->setSpacing(6);
        verticalLayout_part->setObjectName(QStringLiteral("verticalLayout_part"));

        right_2->addLayout(verticalLayout_part);

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

        horizontalLayout_data_2 = new QHBoxLayout();
        horizontalLayout_data_2->setSpacing(6);
        horizontalLayout_data_2->setObjectName(QStringLiteral("horizontalLayout_data_2"));
        label_doc_3 = new QLabel(right_widget_lsd);
        label_doc_3->setObjectName(QStringLiteral("label_doc_3"));
        sizePolicy1.setHeightForWidth(label_doc_3->sizePolicy().hasHeightForWidth());
        label_doc_3->setSizePolicy(sizePolicy1);
        label_doc_3->setMinimumSize(QSize(80, 0));
        label_doc_3->setMaximumSize(QSize(80, 20));

        horizontalLayout_data_2->addWidget(label_doc_3);

        comboBox_data_color = new QComboBox(right_widget_lsd);
        comboBox_data_color->setObjectName(QStringLiteral("comboBox_data_color"));
        sizePolicy2.setHeightForWidth(comboBox_data_color->sizePolicy().hasHeightForWidth());
        comboBox_data_color->setSizePolicy(sizePolicy2);
        comboBox_data_color->setEditable(false);

        horizontalLayout_data_2->addWidget(comboBox_data_color);


        right_2->addLayout(horizontalLayout_data_2);

        verticalWidget_range = new QWidget(right_widget_lsd);
        verticalWidget_range->setObjectName(QStringLiteral("verticalWidget_range"));
        verticalWidget_range->setEnabled(true);
        verticalLayout = new QVBoxLayout(verticalWidget_range);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        horizontalLayout_min = new QHBoxLayout();
        horizontalLayout_min->setSpacing(6);
        horizontalLayout_min->setObjectName(QStringLiteral("horizontalLayout_min"));
        label = new QLabel(verticalWidget_range);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_min->addWidget(label);

        lineEdit_min = new QLineEdit(verticalWidget_range);
        lineEdit_min->setObjectName(QStringLiteral("lineEdit_min"));
        lineEdit_min->setToolTipDuration(-1);
        lineEdit_min->setInputMethodHints(Qt::ImhPreferNumbers);
        lineEdit_min->setClearButtonEnabled(false);

        horizontalLayout_min->addWidget(lineEdit_min);


        verticalLayout->addLayout(horizontalLayout_min);

        horizontalLayout_max = new QHBoxLayout();
        horizontalLayout_max->setSpacing(6);
        horizontalLayout_max->setObjectName(QStringLiteral("horizontalLayout_max"));
        label_2 = new QLabel(verticalWidget_range);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_max->addWidget(label_2);

        lineEdit_max = new QLineEdit(verticalWidget_range);
        lineEdit_max->setObjectName(QStringLiteral("lineEdit_max"));

        horizontalLayout_max->addWidget(lineEdit_max);


        verticalLayout->addLayout(horizontalLayout_max);

        pushButton_range_change = new QPushButton(verticalWidget_range);
        pushButton_range_change->setObjectName(QStringLiteral("pushButton_range_change"));
        sizePolicy.setHeightForWidth(pushButton_range_change->sizePolicy().hasHeightForWidth());
        pushButton_range_change->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton_range_change, 0, Qt::AlignRight);


        right_2->addWidget(verticalWidget_range);

        pushButton_line = new QPushButton(right_widget_lsd);
        pushButton_line->setObjectName(QStringLiteral("pushButton_line"));

        right_2->addWidget(pushButton_line);


        horizontalLayout->addWidget(right_widget_lsd, 0, Qt::AlignTop);

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
        menu->addAction(action_LSDyna);

        retranslateUi(vtkShowerClass);

        comboBox_data_color->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(vtkShowerClass);
    } // setupUi

    void retranslateUi(QMainWindow *vtkShowerClass)
    {
        vtkShowerClass->setWindowTitle(QApplication::translate("vtkShowerClass", "vtkShower", 0));
        action->setText(QApplication::translate("vtkShowerClass", "\346\211\223\345\274\200k\346\226\207\344\273\266", 0));
        action_LSDyna->setText(QApplication::translate("vtkShowerClass", "\346\211\223\345\274\200LSDyna\346\226\207\344\273\266\345\272\223", 0));
        pushButton_play->setText(QApplication::translate("vtkShowerClass", "\346\222\255\346\224\276", 0));
        pushButton_stop->setText(QApplication::translate("vtkShowerClass", "\345\201\234\346\255\242", 0));
        label_frame->setText(QApplication::translate("vtkShowerClass", "0", 0));
        radioButton_solid->setText(QApplication::translate("vtkShowerClass", "\345\256\236\344\275\223\345\215\225\345\205\203", 0));
        radioButton_wareline->setText(QApplication::translate("vtkShowerClass", "\347\272\277\346\241\206\345\215\225\345\205\203", 0));
        radioButton_setnode->setText(QApplication::translate("vtkShowerClass", "\350\212\202\347\202\271\351\233\206\345\220\210", 0));
        radioButton_setSeg->setText(QApplication::translate("vtkShowerClass", "\350\212\202\347\202\271\351\235\242\351\233\206\345\220\210", 0));
        label_doc->setText(QApplication::translate("vtkShowerClass", "\344\275\223\347\274\226\345\217\267\357\274\232", 0));
        radioButton_point_data->setText(QApplication::translate("vtkShowerClass", "\347\202\271\346\225\260\346\215\256", 0));
        radioButton_shell_data->setText(QApplication::translate("vtkShowerClass", "\345\243\263\346\225\260\346\215\256", 0));
        label_doc_4->setText(QApplication::translate("vtkShowerClass", "\344\275\223\347\274\226\345\217\267\357\274\232", 0));
        label_doc_2->setText(QApplication::translate("vtkShowerClass", "\346\225\260\346\215\256\345\220\215\347\247\260\357\274\232", 0));
        label_doc_3->setText(QApplication::translate("vtkShowerClass", "\351\242\234\350\211\262\346\230\240\345\260\204\357\274\232", 0));
        comboBox_data_color->setCurrentText(QString());
        label->setText(QApplication::translate("vtkShowerClass", "\346\234\200\345\260\217\345\200\274\357\274\232", 0));
        label_2->setText(QApplication::translate("vtkShowerClass", "\346\234\200\345\244\247\345\200\274\357\274\232", 0));
        pushButton_range_change->setText(QApplication::translate("vtkShowerClass", "\347\241\256\350\256\244\344\277\256\346\224\271", 0));
        pushButton_line->setText(QApplication::translate("vtkShowerClass", "\346\233\262\347\272\277\350\241\250\347\244\272", 0));
        menu->setTitle(QApplication::translate("vtkShowerClass", "\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class vtkShowerClass: public Ui_vtkShowerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VTKSHOWER_H
