#include "widget.h"
#include "./ui_widget.h"

#include <QDebug>
#include <Geometry>
#include "utils.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    https://stackoverflow.com/questions/28267104/using-eigen-lib-in-my-cmake-project

    using namespace Eigen;
//    Matrix3d m;
//    m = AngleAxis(0.25*3.14, Vector3d::UnitX());
//    Transform T01(AngleAxis(0.25*3.14, Vector3d::UnitX()));
//    T01 = m;

    Affine3d t1(Translation3d(Vector3d(1,1,2)));

//    auto t2 = Vector3d::UnitX();
    Affine3d t2(AngleAxisd(1.34, Vector3d::UnitX()));

    Quaterniond q1(AngleAxisd(1.34, Vector3d::UnitX()));


    printMatrix(t1);
    printMatrix(t2);

    printMatrix(t1*q1);
    printMatrix(t1*t2);

    QString mat;
    for (int i = 0; i<3; ++i)
    {
        for (int j = 0; j<3; ++j)
        {
            auto m = q1.toRotationMatrix();
            mat.append(QString::number(m(i,j), 'g', 2) + "\t");
        }
        qDebug() << qPrintable(mat);
        mat.clear();
    }
    qDebug("\t");



    int a = 234;







}

Widget::~Widget()
{
    delete ui;
}

