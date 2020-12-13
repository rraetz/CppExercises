#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H

#include <iomanip>
#include <iostream>
#include <vector>

#include <nlopt.hpp>

#include <QDebug>

#include "robot.h"

#include "utils.h"

//#include "se3.h"

#include <QMatrix4x4>

#include <random>
#include <chrono>

#include <algorithm>
#include <numeric>
#include <iterator>



typedef struct {
    double a, b;
} my_constraint_data;


// Cost function (structure is predefined by the NLOPT library)
double myvfunc(const std::vector<double> &x, std::vector<double> &grad, void *my_func_data)
{
    // Retrieve robot object
    Robot *r = static_cast<Robot *>(my_func_data);

    // Compute error of pose
    auto Terror = r->endEffectorForwardKinematics(x) - r->m_targetPose;

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
}



std::vector<double> ik(Robot *r)
{
    // Initialize optimizer
    const int N = 6;
    nlopt::opt opt(nlopt::LN_PRAXIS, N);  // GN_CRS_LM or LN_PRAXIS seem to work..

    // Set bounds
    std::vector<double> lowerBound(N);
    std::vector<double> upperBound(N);
    std::fill(lowerBound.begin(), lowerBound.end(), 0);
    std::fill(upperBound.begin(), upperBound.end(), 360);
    opt.set_lower_bounds(lowerBound);
    opt.set_upper_bounds(upperBound);

    // Set objective function, tolerance & max iterations
    opt.set_min_objective(myvfunc, r);
    opt.set_xtol_rel(1e-10);
    opt.set_maxeval(100000);

    // Optimization variables and cost function value
    std::vector<double> x(N);
    double minf;

    // Random number generator
    std::mt19937_64 randGenerator;
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq seedSequence{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    randGenerator.seed(seedSequence);
    std::uniform_real_distribution<double> unif(0, 360);

    // Get initial

    auto angles = r->jointAngles();


    try{
        for(size_t i=0; i<100; ++i)
        {
            // Random initialization of optimization variables
            std::generate(x.begin(), x.end(), [&randGenerator, &unif] {return unif(randGenerator); });

            // Optimize
            opt.optimize(x, minf);
            if (minf < 0.001) break;
        }

        if ( minf >= 0.001)
        {
            x = angles;
        }

        qDebug() << "Found minimum at f(" << x[0] << ","
                 << x[1] << ","
                 << x[2] << ","
                 << x[3] << ","
                 << x[4] << ","
                 << x[5] << ") = "
                 << minf;

        auto T = r->endEffectorForwardKinematics(x);
        printTransformation(T);
    }
    catch(std::exception &e) {
        qDebug() << "nlopt failed: " << e.what();
    }

    return x;
}



#endif // INVERSEKINEMATICS_H
