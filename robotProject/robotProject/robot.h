#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <algorithm>
#include <math.h>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include "joint.h"
#include "coordinatesystem.h"
#include "trajectoryplanner.h"




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

        // Set initial Pose
        std::vector<double> initialAngles(m_joints.size(), 270);
        displayRobot(initialAngles);

    }

    // Destructor
    virtual ~Robot(){}


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
        auto it = jointAngles.begin();
        std::for_each(m_joints.begin(), m_joints.end(), [&it] (Joint *J){J->m_theta = *it; ++it; });

    }


    QMatrix4x4 endEffectorForwardKinematics(const std::vector<double> &jointAngles)
    {
        QMatrix4x4 T;
        auto it = jointAngles.begin();
        std::for_each(m_joints.begin(), m_joints.end(), [&T, &it] (Joint *J) {T = T*J->computeTransform(*it); ++it; });
        return T;
    }



    std::vector<QMatrix4x4> jointsForwardKinematics(const std::vector<double> &jointAngles)
    {
        std::vector<QMatrix4x4> T;
        QMatrix4x4 Ttmp;
        for (size_t i=0; i<m_joints.size(); ++i)
        {
            T.push_back(Ttmp);
            Ttmp = Ttmp * m_joints.at(i)->computeTransform(jointAngles.at(i));
        }
        return T;
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
    }



    void initalizeMovement(std::vector<double> targetJointAngles)
    {
        auto start = this->jointAngles();
        this->m_trajPlanner.init(start, targetJointAngles);
    }



    std::vector<double> jointAngles()
    {
        std::vector<double> angles;
        std::for_each(m_joints.begin(), m_joints.end(), [&angles](Joint *J){std::back_inserter(angles) = J->m_theta;});
        return angles;
    }



    void displayRobot(std::vector<double> jointAngles)
    {
        this->setJointAngles(jointAngles);
        auto T = this->jointsForwardKinematics(jointAngles);
        auto it = T.begin();
        std::for_each(m_joints.begin(), m_joints.end(), [&it] (Joint *J) {J->setPose(*it); ++it; });
        m_endEffector->setPose(this->endEffectorForwardKinematics(jointAngles));
    }



public slots:
    void move()
    {
        auto jointAngles = this->m_trajPlanner.update();
        if (this->m_trajPlanner.m_isMoving) {displayRobot(jointAngles);}
    }

};



#endif // ROBOT_H
