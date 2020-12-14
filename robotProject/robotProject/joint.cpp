#include "joint.h"
#include <math.h>




Joint::Joint(Qt3DCore::QEntity *parent, double theta0, double a, double d, double alpha)
    : Qt3DCore::QEntity(parent)
    , m_theta(0)
    , m_joint(new Cylinder3d(parent))
    , m_linkD(new Cylinder3d(parent))
    , m_linkA(new Cylinder3d(parent))
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


// Methods
// Wrap theta between [0, 360]
void Joint::setTheta(double angle)
{
    if (angle >= 360) {m_theta = angle - 360;}
    else if (angle < 0) {m_theta = angle + 360;}
    else {m_theta = angle;}
}



// Compute and set the pose of the graphical elements with m_theta
void Joint::setPose(QMatrix4x4 T)
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
QMatrix4x4 Joint::computeTransform(double theta)
{
    QMatrix4x4 T;
    T.rotate(theta + m_theta0, 0,1,0);
    T.translate(0, m_d, 0);
    T.translate(0, 0, m_a);
    T.rotate(m_alpha, 0,0,1);
    return T;
}



