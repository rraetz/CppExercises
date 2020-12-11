#ifndef UTILS_H
#define UTILS_H

#include <QDebug>
//#include "spaceTransformations.h"
#include <QMatrix4x4>


//void printTransformation(SE3 m)
//{
//    QString mat;
//    for (int i = 0; i<4; ++i)
//    {
//        for (int j = 0; j<4; ++j)
//        {
//            mat.append(QString::number(m.m_T(i,j), 'g', 2) + "\t");
//        }
//        qDebug() << qPrintable(mat);
//        mat.clear();
//    }
//    qDebug("\t");
//}


void printTransformation(QMatrix4x4 m)
{
    QString mat;
    for (int i = 0; i<4; ++i)
    {
        for (int j = 0; j<4; ++j)
        {
            mat.append(QString::number(m.data()[j*4 + i], 'g', 2) + "\t");
        }
        qDebug() << qPrintable(mat);
        mat.clear();
    }
    qDebug("\t");
}


//class SE3
//{
//public:
//    SE3(QMatrix4x4 T)

//    QMatrix4x4 m_T;

//};

//using Eigen;
//Matrix<qreal, 4, 4, RowMajor> mcopy = m.cast<qreal>();

//QMatrix4x4 qmat(mcopy.data());


//    qDebug().noquote() << QString::fromStdString(T02.printString());




#endif // UTILS_H
