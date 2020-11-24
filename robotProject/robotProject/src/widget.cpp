#include "widget.h"
#include "./ui_widget.h"

#include <QDebug>
#include <Geometry>
#include "utils.h"
#include "spaceTransformations.h"




Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    https://stackoverflow.com/questions/28267104/using-eigen-lib-in-my-cmake-project



    Trans T01;
    Trans T02(2, 3, 4.234);
    Trans T03(2.54, 'e');

    T02.rotX(0.56);

    printTransformation(T01*T02*T03);




}

Widget::~Widget()
{
    delete ui;
}

