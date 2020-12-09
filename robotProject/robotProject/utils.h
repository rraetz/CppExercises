#ifndef UTILS_H
#define UTILS_H

#include <QDebug>
#include "spaceTransformations.h"

void printTransformation(SE3 m)
{
    QString mat;
    for (int i = 0; i<4; ++i)
    {
        for (int j = 0; j<4; ++j)
        {
            mat.append(QString::number(m.m_T(i,j), 'g', 2) + "\t");
        }
        qDebug() << qPrintable(mat);
        mat.clear();
    }
    qDebug("\t");
}

//    qDebug().noquote() << QString::fromStdString(T02.printString());



#endif // UTILS_H
