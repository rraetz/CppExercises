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

#include <random>
#include <chrono>
#include "nlopt.hpp"
#include <thread>
#include <future>
#include <limits>




// Robot needs to be at least a QObject in order to connect it to a timer
// With Qt3DCore::QEntity, we get some more nice features and it makes more sense in this context
class Robot : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    Robot(Qt3DCore::QEntity *parent);
    virtual ~Robot(){}

    // Member variables
    std::vector<Joint*> m_joints; // needs to be pointers because of hoq QObejects work (slots/signals and object tree structure)
    CoordinateSystem *m_base;
    CoordinateSystem *m_endEffector;
    QMatrix4x4 m_targetPose;
    TrajectoryPlanner m_trajPlanner;
    std::vector<nlopt::opt> m_optimizers;

    const double m_INITIAL_JOINT_ANGLE = 270;
    const size_t m_N_SOLVERS = 5;
    const double m_LOWER_ANGLE_LIMIT = 0;
    const double m_UPPER_ANGLE_LIMIT = 360;
    const double m_SOLVER_TOLERANCE = 1e-10;
    const size_t m_MAX_EVALUATIONS = 100000;
    const size_t m_MAX_ITERATIONS = 100;
    const double m_ORIENTATION_WEIGHT = 1000;
    const double m_COST_THRESHOLD = 0.001;

    const double m_J1_THETA0 = 0;
    const double m_J1_A =      0;
    const double m_J1_D =      151.9;
    const double m_J1_ALPHA =  90;
    const double m_J2_THETA0 = 0;
    const double m_J2_A =      -243.0;
    const double m_J2_D =      0;
    const double m_J2_ALPHA =  0;
    const double m_J3_THETA0 = 0;
    const double m_J3_A =      -213.25;
    const double m_J3_D =      0;
    const double m_J3_ALPHA =  0;
    const double m_J4_THETA0 = 0;
    const double m_J4_A =      0;
    const double m_J4_D =      112.35;
    const double m_J4_ALPHA =  -90;
    const double m_J5_THETA0 = 0;
    const double m_J5_A =      0;
    const double m_J5_D =      85.35;
    const double m_J5_ALPHA =  -90;
    const double m_J6_THETA0 = 0;
    const double m_J6_A =      0;
    const double m_J6_D =      81.9;
    const double m_J6_ALPHA =  0;

    // Methods
    void setJointAngles(const std::vector<double> &jointAngles);
    QMatrix4x4 endEffectorForwardKinematics(const std::vector<double> &jointAngles);
    std::vector<QMatrix4x4> jointsForwardKinematics(const std::vector<double> &jointAngles);
    std::vector<double> jointAngles();
    void displayRobot(const std::vector<double> &jointAngles);



// It would be possible to connect to "normal" member functions, but slots illustrate the intent.
public slots:
    void initalizeMovement(const QMatrix4x4 &T);
    void move();

signals:
    void statusMessage(QString message);


private:   
    void initializeInverseKinematicsSolver();
    double IKcostFunction (const std::vector<double> &x);
    static double IKcostFunctionWrapper(const std::vector<double> &x, std::vector<double> &grad, void *data);
    std::vector<double> solveInverseKinematics(const QMatrix4x4 &T);
};



#endif // ROBOT_H
