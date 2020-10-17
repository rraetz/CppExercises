/********************************************************************************
** Form generated from reading UI file 'ekgwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EKGWIDGET_H
#define UI_EKGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_EkgWidget
{
public:
    QCustomPlot *ekgwidget;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *EkgWidget)
    {
        if (EkgWidget->objectName().isEmpty())
            EkgWidget->setObjectName(QString::fromUtf8("EkgWidget"));
        EkgWidget->resize(866, 600);
        ekgwidget = new QCustomPlot(EkgWidget);
        ekgwidget->setObjectName(QString::fromUtf8("ekgwidget"));
        ekgwidget->setGeometry(QRect(20, 20, 821, 431));
        pushButton = new QPushButton(EkgWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 480, 181, 71));
        QPalette palette;
        QBrush brush(QColor(0, 170, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        pushButton->setPalette(palette);
        QFont font;
        font.setPointSize(14);
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 255);"));
        label = new QLabel(EkgWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(240, 520, 251, 31));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        label_2 = new QLabel(EkgWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(240, 480, 311, 31));
        label_2->setFont(font1);

        retranslateUi(EkgWidget);

        QMetaObject::connectSlotsByName(EkgWidget);
    } // setupUi

    void retranslateUi(QWidget *EkgWidget)
    {
        EkgWidget->setWindowTitle(QCoreApplication::translate("EkgWidget", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("EkgWidget", "Plot", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("EkgWidget", "Average Heart Rate [beats/min]:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EkgWidget: public Ui_EkgWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EKGWIDGET_H
