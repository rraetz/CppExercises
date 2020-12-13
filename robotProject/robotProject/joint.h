#ifndef JOINT_H
#define JOINT_H


#include "cylinder3d.h"
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <math.h>



class Joint : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    // Constructor
    Joint(Qt3DCore::QEntity *parent, double theta0, double a, double d, double alpha)
        : Qt3DCore::QEntity(parent)
        , m_joint(new Cylinder3d(parent))
        , m_linkD(new Cylinder3d(parent))
        , m_linkA(new Cylinder3d(parent))
        , m_theta(0)
        , m_theta0(theta0)
        , m_d(d)
        , m_a(a)
        , m_alpha(alpha)
    {
        // Set some basic graphic settings or disable links if not needed
        if (m_a != 0)
        {
            m_linkA->m_mesh->setLength(fabs(m_a));
            m_linkA->m_mesh->setRadius(10);
            m_linkA->m_material->setDiffuse(QColor("grey"));
        }
        else { m_linkA->setEnabled(false); }

        if (m_d != 0)
        {
            m_linkD->m_mesh->setLength(fabs(m_d));
            m_linkD->m_mesh->setRadius(10);
            m_linkD->m_material->setDiffuse(QColor("grey"));
        }
        else { m_linkD->setEnabled(false); }
    }


    // Member variables
    Cylinder3d *m_joint;
    Cylinder3d *m_linkD;
    Cylinder3d *m_linkA;

    double m_theta;
    double m_theta0;
    double m_d;
    double m_a;
    double m_alpha;


    // Methods
    // Compute and set the pose of the graphical elements with m_theta
    void setPose(QMatrix4x4 T)
    {
        m_joint->m_transform->setMatrix(T);
        T.rotate(m_theta + m_theta0, 0,1,0);
        T.translate(0, m_d/2, 0);
        m_linkD->m_transform->setMatrix(T);
        T.translate(0, m_d/2, 0);
        T.translate(0, 0, m_a/2);
        T.rotate(90, 1,0,0);
        m_linkA->m_transform->setMatrix(T);
    }


    // Compute theoretical pose of joint centre with theta
    QMatrix4x4 computeTransform(double theta)
    {
        QMatrix4x4 T;
        T.rotate(theta + m_theta0, 0,1,0);
        T.translate(0, m_d, 0);
        T.translate(0, 0, m_a);
        T.rotate(m_alpha, 0,0,1);
        return T;
    }
};


#endif // JOINT_H
