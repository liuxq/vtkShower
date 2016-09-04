/********************************************************************************
** Form generated from reading UI file 'lineDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEDIALOG_H
#define UI_LINEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "linewidget.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog_line
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    LineWidget *verticalWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog_line)
    {
        if (Dialog_line->objectName().isEmpty())
            Dialog_line->setObjectName(QStringLiteral("Dialog_line"));
        Dialog_line->resize(384, 290);
        verticalLayoutWidget = new QWidget(Dialog_line);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 280, 160, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalWidget = new LineWidget(verticalLayoutWidget);
        verticalWidget->setObjectName(QStringLiteral("verticalWidget"));

        verticalLayout->addWidget(verticalWidget);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(Dialog_line);

        QMetaObject::connectSlotsByName(Dialog_line);
    } // setupUi

    void retranslateUi(QDialog *Dialog_line)
    {
        Dialog_line->setWindowTitle(QApplication::translate("Dialog_line", "\346\233\262\347\272\277\350\241\250\347\244\272", 0));
        pushButton->setText(QApplication::translate("Dialog_line", "\347\241\256\350\256\244", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_line: public Ui_Dialog_line {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEDIALOG_H
