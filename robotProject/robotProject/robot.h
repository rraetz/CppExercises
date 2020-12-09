#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "joint.h"
#include "spaceTransformations.h"
#include <Qt3DCore/QEntity>
#include <QTimer>
#include <math.h>


// Robot needs to be a QObject in order to connect it to a timer
class Robot : public QObject
{
public:
    Robot(Qt3DCore::QEntity *parent)
    {
        m_joints.push_back(Joint(1,2,3,4));
        m_joints.push_back(Joint(2,10,30,2));
        m_joints.at(0).setParent(parent);
        m_joints.at(1).setParent(parent);

    }

    // Member variables
    std::vector<Joint> m_joints;
    QTimer m_timer;
    float m_counter;



    // Methods
    void setAngles(double angle1, double angle2)
    {
        m_joints.at(0).setAngle(angle1);
        m_joints.at(1).setAngle(angle2);
    }

    void setPose()
    {
        ;;
    }

    SE3 forwardKinematics()
    {
        SE3 endEffectorPose;
        for (auto e:m_joints)
        {
            endEffectorPose = endEffectorPose * e.m_T;
        }
        return endEffectorPose;
    }

    void inverseKinematics()
    {
        ;;
    }


public slots:
    void updatePosition()
    {
        ++m_counter;
        qDebug() << "Updating position... counter = " << m_counter;
        float angle1 = sin(m_counter/10);
        float angle2 = cos(m_counter/20);
        setAngles(angle1, angle2);
    }
};

#endif // ROBOT_H
