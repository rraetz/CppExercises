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


typedef struct {
    double a, b;
} my_constraint_data;


double myvfunc(const std::vector<double> &x, std::vector<double> &grad, void *my_func_data)
{
    Robot *r = static_cast<Robot *>(my_func_data);

//    qDebug() << " ";
//    for (auto e:x)
//    {
//        qDebug() << e;
//    }


    r->setJointAngles(x[0], x[1], x[2], x[3], x[4], x[5]);
    auto Tfk = r->computeForwardKinematics();


    auto Tref = r->m_targetPose;

    auto Tres = Tfk - Tref;
//    printTransformation(Tres);

    double T11 = Tres.data()[0];
    double T12 = Tres.data()[1];
    double T13 = Tres.data()[2];

    double T21 = Tres.data()[4];
    double T22 = Tres.data()[5];
    double T23 = Tres.data()[6];

    double T31 = Tres.data()[8];
    double T32 = Tres.data()[9];
    double T33 = Tres.data()[10];


    double T41 = Tres.data()[12];
    double T42 = Tres.data()[13];
    double T43 = Tres.data()[14];


    double resOrientation = T11*T11 + T12*T12 + T13*T13 + T21*T21 + T22*T22 + T23*T23 + T31*T31 + T32*T32 + T33*T33;
//    double resOrientation = T11*T11  + T22*T22 + T33*T33;
    double resPosition = T41*T41 + T42*T42 + T43*T43;
//    double res = T41*T41 + T42*T42 + T43*T43;

//    qDebug() << T11*T11 << " " << T11;

//    double res = 0;

    return resPosition;

//    return sqrt(x[1]);
}


double myvconstraint(const std::vector<double> &x, std::vector<double> &grad, void *data)
{
//    my_constraint_data *d = reinterpret_cast<my_constraint_data*>(data);
//    double a = d->a, b = d->b;

//    return ((a*x[0] + b) * (a*x[0] + b) * (a*x[0] + b) - x[1]);
    return 0;
}



void ik(Robot *r)
{
    nlopt::opt opt(nlopt::LN_COBYLA, 6);

    // Set bounds
    std::vector<double> lb(6);
    lb[0] = 0;
    lb[1] = 0;
    lb[2] = 0;
    lb[3] = 0;
    lb[4] = 0;
    lb[5] = 0;
    opt.set_lower_bounds(lb);

    std::vector<double> ub(6);
    ub[0] = 360;
    ub[1] = 360;
    ub[2] = 360;
    ub[3] = 360;
    ub[4] = 360;
    ub[5] = 360;
    opt.set_upper_bounds(ub);


    // Set objective function
    opt.set_min_objective(myvfunc, r);

    // Set constraints
    my_constraint_data data[6] = { {2,0}, {-1,1}, {-1,1}, {-1,1}, {-1,1}, {-1,1} };
//    opt.add_inequality_constraint(myvconstraint, &data[0], 1e-8);
//    opt.add_inequality_constraint(myvconstraint, &data[1], 1e-8);
//    opt.add_inequality_constraint(myvconstraint, &data[2], 1e-8);
//    opt.add_inequality_constraint(myvconstraint, &data[3], 1e-8);
//    opt.add_inequality_constraint(myvconstraint, &data[4], 1e-8);
//    opt.add_inequality_constraint(myvconstraint, &data[5], 1e-8);

    // Set Tolerance
    opt.set_xtol_rel(1e-5);
    opt.set_maxeval(10000);

    // Initial values
    std::vector<double> x(6);
    x[0] = 90; x[1] = 90;
    double minf;

    try{
        nlopt::result result = opt.optimize(x, minf);
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

    }
    catch(std::exception &e) {
        qDebug() << "nlopt failed: " << e.what();
    }
}



#endif // INVERSEKINEMATICS_H
