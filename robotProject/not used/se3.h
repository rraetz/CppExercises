#ifndef SE3_H
#define SE3_H


#include <QMatrix4x4>
#include <QDebug>


class SE3 : public QMatrix4x4
{
public:

    SE3()
    {
        this->setToIdentity();
    }

    virtual ~SE3(){}

    void trans(double x, double y, double z)
    {
        this->translate(x,y,z);
    }

    void rotX(double angle)
    {
        this->rotate(angle, 1,0,0);
    }

    void rotY(double angle)
    {
        this->rotate(angle, 0,1 ,0);
    }

    void rotZ(double angle)
    {
        this->rotate(angle, 0, 0, 1);
    }


    void poseEulerZYZ(double x, double y, double z, double rotZ1, double rotY, double rotZ2)
    {
        this->setToIdentity();
        this->trans(x,y,z);
        this->rotZ(rotZ1);
        this->rotY(rotY);
        this->rotZ(rotZ2);
    }

//    QMatrix4x4 qt3DgraphicTransform()
//    {
//        float data[16];
//        this->copyDataTo(data);
//        QMatrix4x4 T(data);
//        QMatrix4x4 Trot;
//        Trot.rotate(-90, 1,0,0);
//        Trot.rotate(-90, 0,0,1);

//        return Trot*T;
//    }


    void print()
    {
        QString mat;
        for (int i = 0; i<4; ++i)
        {
            for (int j = 0; j<4; ++j)
            {
                mat.append(QString::number(this->data()[j*4 + i], 'g', 2) + "\t");
            }
            qDebug() << qPrintable(mat);
            mat.clear();
        }
        qDebug("\t");
    }



};




#endif // SE3_H
