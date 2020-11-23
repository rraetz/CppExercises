/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *play_pushButton;
    QComboBox *comboBox;
    QSlider *frameRateSlider;
    QSpacerItem *verticalSpacer;
    QLabel *frameRate_label;
    QWidget *videoWidgetHolder;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->setEnabled(true);
        Widget->resize(1104, 622);
        verticalLayout_2 = new QVBoxLayout(Widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        play_pushButton = new QPushButton(Widget);
        play_pushButton->setObjectName(QString::fromUtf8("play_pushButton"));
        play_pushButton->setMinimumSize(QSize(81, 81));
        play_pushButton->setMaximumSize(QSize(81, 81));
        play_pushButton->setBaseSize(QSize(0, 0));

        verticalLayout->addWidget(play_pushButton);

        comboBox = new QComboBox(Widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEditable(false);

        verticalLayout->addWidget(comboBox);

        frameRateSlider = new QSlider(Widget);
        frameRateSlider->setObjectName(QString::fromUtf8("frameRateSlider"));
        frameRateSlider->setMinimum(0);
        frameRateSlider->setOrientation(Qt::Vertical);

        verticalLayout->addWidget(frameRateSlider);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        frameRate_label = new QLabel(Widget);
        frameRate_label->setObjectName(QString::fromUtf8("frameRate_label"));
        frameRate_label->setMaximumSize(QSize(150, 150));

        verticalLayout->addWidget(frameRate_label);


        horizontalLayout->addLayout(verticalLayout);

        videoWidgetHolder = new QWidget(Widget);
        videoWidgetHolder->setObjectName(QString::fromUtf8("videoWidgetHolder"));

        horizontalLayout->addWidget(videoWidgetHolder);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        play_pushButton->setText(QCoreApplication::translate("Widget", "Play", nullptr));
        frameRate_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
