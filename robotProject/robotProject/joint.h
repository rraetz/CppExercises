#ifndef JOINT_H
#define JOINT_H

#include "spaceTransformations.h"
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <QtMath>

#include "cylinder3d.h"

#include <Qt3DRender/QGeometryRenderer>



class Joint : public Cylinder3d
{
public:
    Joint(Qt3DCore::QEntity *parent)
        : Cylinder3d(parent)
        , m_theta(0)
        , m_theta0(0)
        , m_d(0)
        , m_a(0)
        , m_alpha(0)
    {
        // Initial Pose
        this->setDH(m_theta0, m_d, m_a, m_alpha);
        qDebug() << " Joint construced";
    }

    ~Joint()
    {
        qDebug() << " Joint destruced";
    }


    // Member variables
//    SE3 m_T;
    double m_theta;
    double m_theta0;
    double m_d;
    double m_a;
    double m_alpha;

    // Methods
    void setDH(double theta0, double d, double a, double alpha)
    {
        m_theta0 = theta0;
        m_d = d;
        m_a = a;
        m_alpha = alpha;
    }



    QMatrix4x4 computePose(QMatrix4x4 &T)
    {
        // Eigen matrix
//        m_T = SE3(theta, m_d, m_a, m_alpha);

        T.rotate(qRadiansToDegrees(m_theta + m_theta0), QVector3D(0.0f, 0.0f, 1.0f));
        T.translate(0.0, 0.0f, m_d);
        T.translate(m_a, 0.0, 0.0f);
        T.rotate(qRadiansToDegrees(m_alpha), QVector3D(1.0f, 0.0f, 0.0f));

        m_transform->setMatrix(T);
        return T;
    }

};


#endif // JOINT_H
