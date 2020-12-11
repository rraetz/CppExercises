#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H

#include <iomanip>
#include <iostream>
#include <vector>

#include <nlopt.hpp>

#include <QDebug>

#include "robot.h"

#include "utils.h"

#include "se3.h"

#include <QMatrix4x4>

#include <random>
#include <chrono>



typedef struct {
    double a, b;
} my_constraint_data;


double myvfunc(const std::vector<double> &x, std::vector<double> &grad, void *my_func_data)
{
    // Retrieve robot object
    Robot *r = static_cast<Robot *>(my_func_data);

    r->setJointAngles(x[0], x[1], x[2], x[3], x[4], x[5]);
    auto Tfk = r->computeForwardKinematics();
    auto Tref = r->m_targetPose;
    auto Tres = Tfk - Tref;

    // Get orientation
    double T11 = Tres.data()[0];
    double T12 = Tres.data()[1];
    double T13 = Tres.data()[2];
    double T21 = Tres.data()[4];
    double T22 = Tres.data()[5];
    double T23 = Tres.data()[6];
    double T31 = Tres.data()[8];
    double T32 = Tres.data()[9];
    double T33 = Tres.data()[10];

    // Get position
    double T41 = Tres.data()[12];
    double T42 = Tres.data()[13];
    double T43 = Tres.data()[14];

    // Compute cost
    double costOrientation = T11*T11 + T12*T12 + T13*T13 + T21*T21 + T22*T22 + T23*T23 + T31*T31 + T32*T32 + T33*T33;
    double costPosition = T41*T41 + T42*T42 + T43*T43;
    return costOrientation*1000 + costPosition;
}



void ik(Robot *r)
{

    int N = 6;
    nlopt::opt opt(nlopt::LN_PRAXIS, N);  // GN_CRS_LM or LN_PRAXIS seem to work..
//    nlopt::opt opt(nlopt::GN_CRS2_LM, N);  // GN_CRS2_LM or LN_PRAXIS seem to work..


    // Set bounds
    std::vector<double> lb(N);
    lb[0] = 0;
    lb[1] = 0;
    lb[2] = 0;
    lb[3] = 0;
    lb[4] = 0;
    lb[5] = 0;
    opt.set_lower_bounds(lb);

    std::vector<double> ub(N);
//    ub[0] = 180;
//    ub[1] = 180;
//    ub[2] = 180;
//    ub[3] = 180;
//    ub[4] = 180;
//    ub[5] = 180;
    ub[0] = 360;
    ub[1] = 360;
    ub[2] = 360;
    ub[3] = 360;
    ub[4] = 360;
    ub[5] = 360;
    opt.set_upper_bounds(ub);

    // Set objective function
    opt.set_min_objective(myvfunc, r);

    // Set Tolerance
    opt.set_xtol_rel(1e-10);
    opt.set_maxeval(100000);

    // Initial values
    std::vector<double> x(N);
//    x[0] = 90;
//    x[1] = 90;
//    x[2] = 90;
//    x[3] = 90;
//    x[4] = 90;
//    x[5] = 90;
    x[0] = 0;
    x[1] = 0;
    x[2] = 0;
    x[3] = 0;
    x[4] = 0;
    x[5] = 0;


    double minf;

    std::mt19937_64 randomNumberGenerator;
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    randomNumberGenerator.seed(ss);
    std::uniform_real_distribution<double> unif(0, 1);

    try{
        for(int i=0; i<100; ++i)
        {
            nlopt::result result = opt.optimize(x, minf);
            if (minf < 0.001) break;

            for (auto &e:x)
            {
                  e = unif(randomNumberGenerator)*180;
            }
        }
        qDebug() << "Found minimum at f(" << x[0] << ","
                 << x[1] << ","
                 << x[2] << ","
                 << x[3] << ","
                 << x[4] << ","
                 << x[5] << ") = "
                 << minf;

//        r->setJointAngles(x[0], x[1], x[2], x[3], x[4], x[5]);
        auto T = r->computeForwardKinematics();
        printTransformation(T);

//        T = T-r->m_targetPose;
//        printTransformation(T);

        r->computeAndSetForwardKinematics();


    }
    catch(std::exception &e) {
        qDebug() << "nlopt failed: " << e.what();
    }
}



#endif // INVERSEKINEMATICS_H
