
#include "robot.h"

// Robot needs to be at least a QObject in order to connect it to a timer
// With Qt3DCore::QEntity, we get some more nice features and it makes more sense in this context
Robot::Robot(Qt3DCore::QEntity *parent)
    : Qt3DCore::QEntity(parent)
    , m_base(new CoordinateSystem(parent))
    , m_endEffector(new CoordinateSystem(parent))
{
    // Create a 6 DoF robot (Universal Robotics UR3)
    m_joints.push_back(new Joint(parent, m_J1_THETA0, m_J1_A, m_J1_D, m_J1_ALPHA));
    m_joints.push_back(new Joint(parent, m_J2_THETA0, m_J2_A, m_J2_D, m_J2_ALPHA));
    m_joints.push_back(new Joint(parent, m_J3_THETA0, m_J3_A, m_J3_D, m_J3_ALPHA));
    m_joints.push_back(new Joint(parent, m_J4_THETA0, m_J4_A, m_J4_D, m_J4_ALPHA));
    m_joints.push_back(new Joint(parent, m_J5_THETA0, m_J5_A, m_J5_D, m_J5_ALPHA));
    m_joints.push_back(new Joint(parent, m_J6_THETA0, m_J6_A, m_J6_D, m_J6_ALPHA));

    // Set initial Pose
    std::vector<double> initialAngles(m_joints.size(), m_INITIAL_JOINT_ANGLE);
    this->displayRobot(initialAngles);

    // Initialize IK solver
    this->initializeInverseKinematicsSolver();
}



// Methods

// Set joint angle variables in joints
void Robot::setJointAngles(const std::vector<double> &jointAngles)
{
    auto it = jointAngles.begin();
    std::for_each(m_joints.begin(), m_joints.end(), [&it] (Joint *J){J->setTheta(*it); ++it; });

}


// Compute forward kinematics for end effector
QMatrix4x4 Robot::endEffectorForwardKinematics(const std::vector<double> &jointAngles)
{
    QMatrix4x4 T;
    auto it = jointAngles.begin();
    std::for_each(m_joints.begin(), m_joints.end(), [&T, &it] (Joint *J) {T = T*J->computeTransform(*it); ++it; });
    return T;
}


// Compute forward kinematics for all joints
std::vector<QMatrix4x4> Robot::jointsForwardKinematics(const std::vector<double> &jointAngles)
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
std::vector<double> Robot::jointAngles()
{
    std::vector<double> angles;
    std::for_each(m_joints.begin(), m_joints.end(), [&angles](Joint *J){std::back_inserter(angles) = J->m_theta; });
    return angles;
}


// Display robot with given joint angles
void Robot::displayRobot(const std::vector<double> &jointAngles)
{
    setJointAngles(jointAngles);
    auto T = jointsForwardKinematics(jointAngles);
    auto it = T.begin();
    std::for_each(m_joints.begin(), m_joints.end(), [&it] (Joint *J) {J->setPose(*it); ++it; });
    m_endEffector->setPose(endEffectorForwardKinematics(jointAngles));
}



// It would be possible to connect to "normal" member functions, but slots illustrate the intent.
void Robot::initalizeMovement(const QMatrix4x4 &T)
{
    auto targetJointAngles = solveInverseKinematics(T);
    auto start = jointAngles();
    m_trajPlanner.init(start, targetJointAngles);
}

void Robot::move()
{
    auto jointAngles = m_trajPlanner.update();
    if (m_trajPlanner.m_isMoving) {displayRobot(jointAngles);}
}


// Initialization of IK solver
void Robot::initializeInverseKinematicsSolver()
{
    // Initialize optimizers
    m_optimizers = std::vector<nlopt::opt>(m_N_SOLVERS, nlopt::opt(nlopt::LN_PRAXIS, m_joints.size()));

    // Set bounds
    std::vector<double> lowerBound(m_joints.size());
    std::vector<double> upperBound(m_joints.size());
    std::fill(lowerBound.begin(), lowerBound.end(), m_LOWER_ANGLE_LIMIT);
    std::fill(upperBound.begin(), upperBound.end(), m_UPPER_ANGLE_LIMIT);
    for_each(m_optimizers.begin(), m_optimizers.end(), [&lowerBound](nlopt::opt &o){o.set_lower_bounds(lowerBound); });
    for_each(m_optimizers.begin(), m_optimizers.end(), [&upperBound](nlopt::opt &o){o.set_upper_bounds(upperBound); });

    // Set objective function, tolerance & max iterations
    for_each(m_optimizers.begin(), m_optimizers.end(), [this] (nlopt::opt &o) {o.set_min_objective(IKcostFunctionWrapper, this); });
    for_each(m_optimizers.begin(), m_optimizers.end(), [this](nlopt::opt &o){o.set_xtol_rel(m_SOLVER_TOLERANCE); });
    for_each(m_optimizers.begin(), m_optimizers.end(), [this](nlopt::opt &o){o.set_maxeval(m_MAX_EVALUATIONS); });
}



double Robot::IKcostFunction (const std::vector<double> &x)
{
    // Compute error of pose
    auto Terror = endEffectorForwardKinematics(x) - m_targetPose;

    // Get orientation
    std::vector<double> orientationError;
    orientationError.reserve(9);
    orientationError.push_back(Terror.data()[0]);
    orientationError.push_back(Terror.data()[1]);
    orientationError.push_back(Terror.data()[2]);
    orientationError.push_back(Terror.data()[4]);
    orientationError.push_back(Terror.data()[5]);
    orientationError.push_back(Terror.data()[6]);
    orientationError.push_back(Terror.data()[8]);
    orientationError.push_back(Terror.data()[9]);
    orientationError.push_back(Terror.data()[10]);

    // Get position
    std::vector<double> positionError;
    positionError.reserve(3);
    positionError.push_back(Terror.data()[12]);
    positionError.push_back(Terror.data()[13]);
    positionError.push_back(Terror.data()[14]);

    // Compute and return cost (sum of error squares)
    double costOrientation = std::inner_product(orientationError.begin(), orientationError.end(),
                                                orientationError.begin(), 0.0);
    double costPosition = std::inner_product(positionError.begin(), positionError.end(),
                                                positionError.begin(), 0.0);
    return costOrientation*m_ORIENTATION_WEIGHT + costPosition;
};



// Wrapper around costFunction according to NLOPT specs
double Robot::IKcostFunctionWrapper(const std::vector<double> &x, std::vector<double> &grad, void *data)
{
    Robot *r = reinterpret_cast<Robot*>(data);
    return r->IKcostFunction(x);
}



// Solve inverse kinematics
std::vector<double> Robot::solveInverseKinematics(const QMatrix4x4 &T)
{
    // Set target pose
    m_targetPose = T;

    // Labmda that optimizes and that will be executed in threads
    auto optimize ([this] (nlopt::opt o) {

        // Initialize random number generator, variable vector & cost
        std::random_device randomDevice;
        std::mt19937 randGenerator(randomDevice());
        std::uniform_real_distribution<double> uniformDist(m_LOWER_ANGLE_LIMIT, m_UPPER_ANGLE_LIMIT);
        std::vector<double> x(m_joints.size());
        double minCost;

        for (size_t i=0; i<m_MAX_ITERATIONS; ++i)
        {
            // Initialize randomly and optimize
            std::generate(x.begin(), x.end(), [&randGenerator, &uniformDist] {return uniformDist(randGenerator); });
            o.optimize(x, minCost);

            // Accept solution if it's good enough
            if (minCost < m_COST_THRESHOLD) { break; }
        }
        // Add cost value at end of result
        x.push_back(minCost);
        return x;
    });

    // Create threads
    std::vector<std::future<std::vector<double>>> threadFutures;
    std::transform(m_optimizers.begin(), m_optimizers.end(),
                   std::back_inserter(threadFutures),
                   [optimize](nlopt::opt o){ return std::async(optimize, o); });

    // Call solvers and retrieve best solution
    std::vector<double> solution;
    double cost = std::numeric_limits<double>::max();
    for (auto &e:threadFutures)
    {
        auto x = e.get();
        auto costNew = x.back();
        x.pop_back();
        qDebug() <<"Joint angles: " << x << " Cost: " << costNew;
        if (costNew < cost) {solution = x; }
        cost = costNew;
    }
    qDebug() << "Best solution: " << solution ;

    // Check feasibility
    if (cost < m_COST_THRESHOLD)
    {
        statusMessage("Solution found");
    }
    else
    {
        statusMessage("Not feasible");
        solution = jointAngles();
    }
    return solution;
}
