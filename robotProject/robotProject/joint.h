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



class Joint
{
public:
    Joint(Qt3DCore::QEntity *parent)
        : m_joint(new Cylinder3d(parent))
        , m_linkD(new Cylinder3d(parent))
        , m_linkA(new Cylinder3d(parent))
        , m_theta(0)
        , m_theta0(0)
        , m_d(0)
        , m_a(0)
        , m_alpha(0)
    {
        qDebug() << " Joint construced";
    }

    ~Joint()
    {
        qDebug() << " Joint destruced";
    }


    // Member variables
//    SE3 m_T;
    Cylinder3d *m_joint;
    Cylinder3d *m_linkD;
    Cylinder3d *m_linkA;
    double m_theta;
    double m_theta0;
    double m_d;
    double m_a;
    double m_alpha;

    // Methods
    void setDH(double theta0, double a, double d, double alpha)
    {
        m_theta0 = theta0;
        m_d = d;
        m_a = a;
        m_alpha = alpha;

        if (m_a != 0)
        {
            m_linkA->m_mesh->setLength(fabs(m_a));
            m_linkA->m_mesh->setRadius(3);
            m_linkA->m_material->setDiffuse(QColor("grey"));
        }
        else
        {
            m_linkA->setEnabled(false);
        }


        if (m_d != 0)
        {
            m_linkD->m_mesh->setLength(fabs(m_d));
            m_linkD->m_mesh->setRadius(3);
            m_linkD->m_material->setDiffuse(QColor("grey"));
        }
        else
        {
            m_linkD->setEnabled(false);
        }


    }



    QMatrix4x4 computePose(QMatrix4x4 &T)
    {
        // Eigen matrix
//        m_T = SE3(theta, m_d, m_a, m_alpha);

        QMatrix4x4 Ttmp;

        m_joint->m_transform->setMatrix(T);

        T.rotate(qRadiansToDegrees(m_theta + m_theta0), QVector3D(0,1,0));
        T.translate(0, m_d, 0);

        Ttmp = T;
        Ttmp.translate(0, -m_d/2, 0);
        m_linkD->m_transform->setMatrix(Ttmp);

        T.translate(0, 0, m_a);

        Ttmp = T;
        Ttmp.translate(0, 0, -m_a/2);
        Ttmp.rotate(90, QVector3D(1,0,0));
        m_linkA->m_transform->setMatrix(Ttmp);

        T.rotate(qRadiansToDegrees(m_alpha), QVector3D(0,0,1));

        return T;
    }

};


#endif // JOINT_H
