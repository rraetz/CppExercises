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
#include "utils.h"
#include "nlopt.hpp"

#include <thread>
#include <functional>
#include <future>



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
        this->displayRobot(initialAngles);

        // Initialize IK solver
//        this->initializeInverseKinematicsSolver();
    }


    // Destructor
    virtual ~Robot(){}


    // Member variables
    std::vector<Joint*> m_joints; // needs to be pointers because of hoq QObejects work (slots/signals and object tree structure)
    CoordinateSystem *m_base;
    CoordinateSystem *m_endEffector;
    QMatrix4x4 m_targetPose;
    TrajectoryPlanner m_trajPlanner;
    nlopt::opt m_optimizer;
    std::vector<std::thread> m_threads;



    // Methods

    // Set joint angle variables in joints
    void setJointAngles(const std::vector<double> &jointAngles)
    {
        auto it = jointAngles.begin();
        std::for_each(m_joints.begin(), m_joints.end(), [&it] (Joint *J){J->setTheta(*it); ++it; });

    }


    // Compute forward kinematics for end effector
    QMatrix4x4 endEffectorForwardKinematics(const std::vector<double> &jointAngles)
    {
        QMatrix4x4 T;
        auto it = jointAngles.begin();
        std::for_each(m_joints.begin(), m_joints.end(), [&T, &it] (Joint *J) {T = T*J->computeTransform(*it); ++it; });
        return T;
    }


    // Compute forward kinematics for all joints
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


    // Collect joint angles and get the as vector
    std::vector<double> jointAngles()
    {
        std::vector<double> angles;
        std::for_each(m_joints.begin(), m_joints.end(), [&angles](Joint *J){std::back_inserter(angles) = J->m_theta; });
        return angles;
    }


    // Display robot with given joint angles
    void displayRobot(const std::vector<double> &jointAngles)
    {
        this->setJointAngles(jointAngles);
        auto T = this->jointsForwardKinematics(jointAngles);
        auto it = T.begin();
        std::for_each(m_joints.begin(), m_joints.end(), [&it] (Joint *J) {J->setPose(*it); ++it; });
        m_endEffector->setPose(this->endEffectorForwardKinematics(jointAngles));
    }



// It would be possible to connect to "normal" member functions, but slots illustrate the intent.
public slots:
    void initalizeMovement(const QMatrix4x4 &T)
    {

//        std::future<std::vector<double>> fu = std::async(&Robot::solveInverseKinematics, this, std::ref(T));

//        std::future<std::vector<double>> fu2 = std::async(&Robot::solveInverseKinematics, this, std::ref(T));

//        auto targetJointAngles = fu.get();
//        auto targetJointAngles2 = fu2.get();

//        qDebug() << targetJointAngles;
//        qDebug() << targetJointAngles2;



//        std::thread th1(&Robot::solveInverseKinematics, this, std::ref(T));

//        th1.join();

        auto targetJointAngles = this->solveInverseKinematics(T);
        auto start = this->jointAngles();
        this->m_trajPlanner.init(start, targetJointAngles);
    }

    void move()
    {
        auto jointAngles = this->m_trajPlanner.update();
        if (this->m_trajPlanner.m_isMoving) {displayRobot(jointAngles);}
    }



signals:
    void statusMessage(QString message);



private:
    double IKcostFunction (const std::vector<double> &x)
    {
        // Compute error of pose
        auto Terror = this->endEffectorForwardKinematics(x) - this->m_targetPose;

        // Get orientation
        std::vector<double> orientationError(9);
        orientationError.at(0) = Terror.data()[0];
        orientationError.at(1) = Terror.data()[1];
        orientationError.at(2) = Terror.data()[2];
        orientationError.at(3) = Terror.data()[4];
        orientationError.at(4) = Terror.data()[5];
        orientationError.at(5) = Terror.data()[6];
        orientationError.at(6) = Terror.data()[8];
        orientationError.at(7) = Terror.data()[9];
        orientationError.at(8) = Terror.data()[10];

        // Get position
        std::vector<double> positionError(3);
        positionError.at(0) = Terror.data()[12];
        positionError.at(1) = Terror.data()[13];
        positionError.at(2) = Terror.data()[14];

        // Compute and return cost (sum of error squares)
        double costOrientation = std::inner_product(orientationError.begin(), orientationError.end(),
                                                    orientationError.begin(), 0.0);
        double costPosition = std::inner_product(positionError.begin(), positionError.end(),
                                                    positionError.begin(), 0.0);
        return costOrientation*1000 + costPosition;
    };


    // Wrapper around costFunction according to NLOPT specs
    static double IKcostFunctionWrapper(const std::vector<double> &x, std::vector<double> &grad, void *data)
    {
        Robot *r = reinterpret_cast<Robot*>(data);
        return r->IKcostFunction(x);
    }

    // Initialization of IK solver
    void initializeInverseKinematicsSolver()
    {

        // Initialize optimizer
        size_t N = m_joints.size();
        m_optimizer = nlopt::opt(nlopt::LN_PRAXIS, N);

        // Set bounds
        std::vector<double> lowerBound(N);
        std::vector<double> upperBound(N);
        std::fill(lowerBound.begin(), lowerBound.end(), 0);
        std::fill(upperBound.begin(), upperBound.end(), 360);
        m_optimizer.set_lower_bounds(lowerBound);
        m_optimizer.set_upper_bounds(upperBound);

        // Set objective function, tolerance & max iterations
        m_optimizer.set_min_objective(IKcostFunctionWrapper, this);
        m_optimizer.set_xtol_rel(1e-10);
        m_optimizer.set_maxeval(100000);


    }


    // Solve inverse kinematics
    std::vector<double> solveInverseKinematics(const QMatrix4x4 &T)
    {
        // Initialize optimizer
        size_t N = m_joints.size();
        size_t M = 4;
        std::vector<nlopt::opt> optims(M, nlopt::opt(nlopt::LN_PRAXIS, N));


        // Set bounds
        std::vector<double> lowerBound(N);
        std::vector<double> upperBound(N);
        std::fill(lowerBound.begin(), lowerBound.end(), 0);
        std::fill(upperBound.begin(), upperBound.end(), 360);
        for_each(optims.begin(), optims.end(), [&lowerBound](nlopt::opt &o){o.set_lower_bounds(lowerBound); });
        for_each(optims.begin(), optims.end(), [&upperBound](nlopt::opt &o){o.set_upper_bounds(upperBound); });


        // Set objective function, tolerance & max iterations
        for_each(optims.begin(), optims.end(), [this] (nlopt::opt &o) {o.set_min_objective(this->IKcostFunctionWrapper, this); });
        for_each(optims.begin(), optims.end(), [](nlopt::opt &o){o.set_xtol_rel(1e-10); });
        for_each(optims.begin(), optims.end(), [](nlopt::opt &o){o.set_maxeval(100000); });


        // Set target pose
        m_targetPose = T;


        // Optimization variables and cost function value
        auto lambda ([this] (nlopt::opt o) {

            // Random number generator
            std::random_device randomDevice;
            std::mt19937 randGenerator(randomDevice());
            std::uniform_real_distribution<double> uniformDist(0, 360);

            std::vector<double> x(m_joints.size());
            double minCost;
            auto prevJointAngles = this->jointAngles();

            try{
                for(size_t i=0; i<100; ++i)
                {
                    // Random initialization of optimization variables
                    std::generate(x.begin(), x.end(), [&randGenerator, &uniformDist] {return uniformDist(randGenerator); });

                    // Optimize
                    o.optimize(x, minCost);
                    if (minCost < 0.001)
                    {
                        this->statusMessage("Solution found");
                        break;
                    }
                }

                if ( minCost >= 0.001)
                {
                    this->statusMessage("Not feasible");
                    x = prevJointAngles;
                }

                qDebug() << "Found minimum at f(" << x[0] << ","
                         << x[1] << ","
                         << x[2] << ","
                         << x[3] << ","
                         << x[4] << ","
                         << x[5] << ") = "
                         << minCost;

                auto T = this->endEffectorForwardKinematics(x);
                printTransformation(T);
            }
            catch(std::exception &e) {
                qDebug() << "nlopt failed: " << e.what();
            }

            x.push_back(minCost);
            return x;
        });



        std::vector< std::future<std::vector<double>> > fus;

        for (size_t i=0; i<M; ++i)
        {
            fus.push_back(std::async(lambda, optims.at(i)));
        }


        std::vector<double> sol;
        double costPrev = 1000;
        for (auto &e:fus)
        {
            auto x = e.get();
            auto cost = x.back();
            x.pop_back();
            qDebug() <<"Solution: " << x << " Cost: " << cost;
            if (cost < costPrev) {sol = x; qDebug() << "Final cost: " << cost;}
            costPrev = cost;
        }
        return sol;

    }



};



#endif // ROBOT_H
