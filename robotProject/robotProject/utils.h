#ifndef UTILS_H
#define UTILS_H

#include <QDebug>
#include <QMatrix4x4>


// print a QMatrix4x4, must be inline for use in QObjects // or declare in in source file
inline void printTransformation(QMatrix4x4 m)
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



#endif // UTILS_H
