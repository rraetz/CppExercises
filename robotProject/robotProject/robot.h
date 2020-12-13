#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "joint.h"
#include "spaceTransformations.h"
#include <Qt3DCore/QEntity>
#include <QTimer>
#include <math.h>

#include <Qt3DCore/QTransform>

#include <QtMath>

#include "coordinatesystem.h"
#include "trajectoryplanner.h"
#include <algorithm>

#include "utils.h"


constexpr double J0_THETA0 = 0;
constexpr double J0_D =      0;
constexpr double J0_A =      0;
constexpr double J0_ALPHA =  0;


// Robot needs to be at least a QObject in order to connect it to a timer
// With Qt3DCore::QEntity, we get some more nice features and it makes more sense in this context
class Robot : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    Robot(Qt3DCore::QEntity *parent)
        : Qt3DCore::QEntity(parent)
        , m_base(new CoordinateSystem(parent))
        , m_endEffector(new CoordinateSystem(parent))
    {
        // Create a 6 DoF robot (Universal Robotics UR3)
        m_joints.push_back(new Joint(parent, 0,0,151.9,90));
        m_joints.push_back(new Joint(parent, 0,-243.0,0,0));
        m_joints.push_back(new Joint(parent, 0,-213.25,0,0));
        m_joints.push_back(new Joint(parent, 0,0,112.35,-90));
        m_joints.push_back(new Joint(parent, 0,0,85.35,-90));
        m_joints.push_back(new Joint(parent, 0,0,81.9,0));

//        this->setJointAngles(std::vector<double>(m_joints.size(),0));
        this->computeForwardKinematics();

        qDebug() << "Robot constructed";
    }

    // Destructor
    virtual ~Robot()
    {
        qDebug() << "Robot destructed";
    }

    // Member variables
    std::vector<Joint*> m_joints; // needs to be pointers because of hoq QObejects work (slots/signals and object tree structure)
    CoordinateSystem *m_base;
    CoordinateSystem *m_endEffector;
    QMatrix4x4 m_targetPose;
    TrajectoryPlanner m_trajPlanner;


    // Methods

    // Set joint angle variables in joints
    void setJointAngles(const std::vector<double> &jointAngles)
    {
        for (size_t i=0; i<m_joints.size(); ++i)
        {
            m_joints.at(i)->m_theta = jointAngles.at(i);
        }
    }

    // Compute forward kinematics
    QMatrix4x4 computeForwardKinematics()
    {
        QMatrix4x4 T;
        T.setToIdentity();
        for (auto e:m_joints)
        {
            T = T*e->computeTransform(e->m_theta);
        }
        return T;
    }

//    QMatrix4x4 computeForwardKinematics(std::vector<double> jointAngles)
//    {
//        QMatrix4x4 T;
//        T.setToIdentity();
//        for (int i=0; i<6; ++i)
//        {
//            T = T * m_joints.at(i)->computeTransform(jointAngles.at(i));
//        }
//        return T;
//    }

    // Compute forward kinematics and set graphical elements
    void computeAndSetForwardKinematics()
    {
        QMatrix4x4 T;
        T.setToIdentity();
        for (auto e:m_joints)
        {
            e->setPose(T);
            T = e->computePose(T);
        }
        m_endEffector->setPose(T);
    }


    void setTargetPoseFromEulerZYZ(double x, double y, double z, double rotZ1, double rotY, double rotZ2)
    {
        QMatrix4x4 T;
        T.setToIdentity();
        T.translate(y,z,x);
        T.rotate(rotZ1, 0,1,0);
        T.rotate(rotY, 1,0,0);
        T.rotate(rotZ2, 0,1,0);
        m_targetPose = T;

        // Copy current theta to thetaSTart before optimizer starts messing around
        std::for_each(m_joints.begin(), m_joints.end(), [](Joint *J){J->m_thetaStart = J->m_theta;});
    }


    void initalizeMovement()
    {
        std::vector<double> start;
        std::vector<double> target;
        for (size_t i=0; i<m_joints.size(); ++i)
        {
            start.push_back(m_joints.at(i)->m_thetaStart);
            target.push_back(m_joints.at(i)->m_theta);
        }
        this->m_trajPlanner.init(start, target);
    }


public slots:
    void move()
    {
        auto angles = this->m_trajPlanner.update();
        if (this->m_trajPlanner.m_isMoving)
        {
            this->setJointAngles(angles);
            this->computeAndSetForwardKinematics();
        }
        else
        {
            for (size_t i=0; i<m_joints.size(); ++i)
            {
                m_joints.at(i)->m_thetaTarget = angles.at(i);
            }
        }
    }



    void setPose(double x, double y, double z, double rotZ1, double rotY, double rotZ2)
    {
        this->setTargetPoseFromEulerZYZ(x, y, z, rotZ1, rotY, rotZ2);

    }



    void disable(bool enabled)
    {
        m_joints.at(0)->m_joint->setEnabled(enabled);
    }
};



#endif // ROBOT_H
