#ifndef UTILS_H
#define UTILS_H

#include <QDebug>
#include <Geometry>

void printMatrix(Eigen::Affine3d m)
{
    QString mat;
    for (int i = 0; i<4; ++i)
    {
        for (int j = 0; j<4; ++j)
        {
            mat.append(QString::number(m(i,j), 'g', 2) + "\t");
        }
        qDebug() << qPrintable(mat);
        mat.clear();
    }
    qDebug("\t");
}



#endif // UTILS_H
