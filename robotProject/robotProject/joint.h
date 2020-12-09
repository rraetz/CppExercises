#ifndef JOINT_H
#define JOINT_H

#include "spaceTransformations.h"


class Joint
{
public:
    Joint(double theta0, double d, double a, double alpha)
        : m_theta0(theta0), m_d(d), m_a(a), m_alpha(alpha)
    {
        this->setAngle(m_theta0);
    }


    SE3 m_T;

    double m_theta0;
    double m_d;
    double m_a;
    double m_alpha;

    void setAngle(double theta)
    {
        m_T = SE3(theta, m_d, m_a, m_alpha);
    }

    // type of joint
    // visual object associated --> seperate in different file?

};


#endif // JOINT_H
