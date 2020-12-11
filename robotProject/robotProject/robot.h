#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "joint.h"
#include "spaceTransformations.h"
#include <Qt3DCore/QEntity>
#include <QTimer>
#include <math.h>

#include <Qt3DCore/QTransform>

#include "utils.h"

#include <QtMath>

#include "coordinatesystem.h"



constexpr double J0_THETA0 = 0;
constexpr double J0_D =      0;
constexpr double J0_A =      0;
constexpr double J0_ALPHA =  0;


// Robot needs to be at least a QObject in order to connect it to a timer
// With Qt3DCore::QEntity, we get some more nice features and it makes more sense in this context
class Robot : public Qt3DCore::QEntity
{
public:
    Robot(Qt3DCore::QEntity *parent)
        : Qt3DCore::QEntity(parent)
        , m_base(parent)
        , m_endEffector(parent)
        , m_counter(0)
    {
        // Create a 6 DoF robot
        for (int i=0; i<7; ++i)
        {
            m_joints.push_back(new Joint(parent));
        }


        m_joints.at(0)->setDH(0,0,0,0);
        m_joints.at(1)->setDH(0,0,151.9,90);
        m_joints.at(2)->setDH(0,-243.0,0,0);
        m_joints.at(3)->setDH(0,-213.25,0,0);
        m_joints.at(4)->setDH(0,0,112.35,-90);
        m_joints.at(5)->setDH(0,0,85.35,-90);
        m_joints.at(6)->setDH(0,0,81.9,0);

        m_joints.at(0)->m_joint->m_material->setDiffuse(QColor("red"));

        this->setJointAngles(0,0,0,0,0,0);
        this->computeForwardKinematics();

        m_joints.at(0)->m_joint->setEnabled(false);
        qDebug() << "Robot constructed";
    }

    // Destructor
    virtual ~Robot()
    {
        qDebug() << "Robot destructed";
    }

    // Member variables
    std::vector<Joint*> m_joints; // needs to be pointers because of hoq QObejects work (slots/signals and object tree structure)
    CoordinateSystem m_base;
    CoordinateSystem m_endEffector;
    double m_counter;
    QMatrix4x4 m_targetPose;


    // Methods
//    void setPoseEulerXYZ(double x, double y, double z, double rotX, double rotY, double rotZ)
//    {

//    }

    // Set joint angle variables in joints
    void setJointAngles(double a1, double a2, double a3, double a4, double a5, double a6)
    {
        m_joints.at(1)->m_theta = a1;
        m_joints.at(2)->m_theta = a2;
        m_joints.at(3)->m_theta = a3;
        m_joints.at(4)->m_theta = a4;
        m_joints.at(5)->m_theta = a5;
        m_joints.at(6)->m_theta = a6;
    }

    // Compute forward kinematics
    QMatrix4x4 computeForwardKinematics()
    {
        QMatrix4x4 T;
        T.setToIdentity();
        for (auto e:m_joints)
        {
            T = e->computePose(T);
//            qDebug() << T.data()[0];
        }
        return T;
    }

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
        m_endEffector.setPose(T);
    }

    void setTargetPoseFromEulerZYZ(double x, double y, double z, double rotZ1, double rotY, double rotZ2)
    {
        // QT_COORDSYS
        QMatrix4x4 T;
        T.setToIdentity();
        T.translate(y,z,x);
        T.rotate(rotZ1, QVector3D(0,1,0));
        T.rotate(rotY, QVector3D(1,0,0));
        T.rotate(rotZ2, QVector3D(0,1,0));
        m_targetPose = T;
    }

    void setTargetPoseFromJointAngles(double a1, double a2, double a3, double a4, double a5, double a6)
    {
        this->setJointAngles(a1, a2, a3, a4, a5, a6);
        m_targetPose = this->computeForwardKinematics();
    }

    void sayHello()
    {
        qDebug() << "Robot says Hello";
    }



public slots:
    void updatePose()
    {

        ++m_counter;
        float angle1 = 180 + sin(m_counter/50)*45+90;
        float angle2 = 180 + cos(m_counter/100)*45+90;
        this->setJointAngles(angle1, angle2, angle1, angle2, angle2, angle2);
        this->computeAndSetForwardKinematics();
//        auto T = this->computeForwardKinematics();
//        printTransformation(T);

//        if (fmod(m_counter, 10) == 0) this->computeAndSetForwardKinematics();
    }

    void setPoseAndComputeIK(double x, double y, double z, double rotZ1, double rotY, double rotZ2)
    {
        this->setTargetPoseFromEulerZYZ(x, y, z, rotZ1, rotY, rotZ2);
//        ik(this);

    }

    void disable(bool enabled)
    {
        m_joints.at(0)->m_joint->setEnabled(enabled);
    }
};



#endif // ROBOT_H
