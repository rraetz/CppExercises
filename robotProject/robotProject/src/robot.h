#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "joint.h"
#include "spaceTransformations.h"

// TODO
// - put vector with joints on heap
// - factory pattern for joints


class Robot
{
public:
    Robot()
    {
        m_joints.push_back(Joint(1,2,3,4));
        m_joints.push_back(Joint(2,1,3,2));
    }


    // Member variables
    std::vector<Joint> m_joints;

    // Methods
    void setAngles(double angle1, double angle2)
    {
        m_joints.at(0).setAngle(angle1);
        m_joints.at(1).setAngle(angle2);
    }

    void setPose(SE3 pose)
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



};

#endif // ROBOT_H
