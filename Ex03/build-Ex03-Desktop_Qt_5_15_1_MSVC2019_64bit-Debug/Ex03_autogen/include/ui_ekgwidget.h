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
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_EkgWidget
{
public:
    QCustomPlot *ekgwidget;

    void setupUi(QWidget *EkgWidget)
    {
        if (EkgWidget->objectName().isEmpty())
            EkgWidget->setObjectName(QString::fromUtf8("EkgWidget"));
        EkgWidget->resize(866, 600);
        ekgwidget = new QCustomPlot(EkgWidget);
        ekgwidget->setObjectName(QString::fromUtf8("ekgwidget"));
        ekgwidget->setGeometry(QRect(69, 59, 671, 381));

        retranslateUi(EkgWidget);

        QMetaObject::connectSlotsByName(EkgWidget);
    } // setupUi

    void retranslateUi(QWidget *EkgWidget)
    {
        EkgWidget->setWindowTitle(QCoreApplication::translate("EkgWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EkgWidget: public Ui_EkgWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EKGWIDGET_H
