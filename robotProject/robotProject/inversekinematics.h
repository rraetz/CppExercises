#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H

#include <iomanip>
#include <iostream>
#include <vector>

#include <nlopt.hpp>

#include <QDebug>

typedef struct {
    double a, b;
} my_constraint_data;


double myvfunc(const std::vector<double> &x, std::vector<double> &grad, void *my_func_data)
{
    return sqrt(x[1]);
}


double myvconstraint(const std::vector<double> &x, std::vector<double> &grad, void *data)
{
    my_constraint_data *d = reinterpret_cast<my_constraint_data*>(data);
    double a = d->a, b = d->b;

    return ((a*x[0] + b) * (a*x[0] + b) * (a*x[0] + b) - x[1]);
}



void ik()
{
    nlopt::opt opt(nlopt::LN_COBYLA, 2);

    // Set bounds
    std::vector<double> lb(2);
    lb[0] = -HUGE_VAL; lb[1] = 0;
    opt.set_lower_bounds(lb);

    // Set objective function
    opt.set_min_objective(myvfunc, NULL);

    // Set constraints
    my_constraint_data data[2] = { {2,0}, {-1,1} };
    opt.add_inequality_constraint(myvconstraint, &data[0], 1e-8);
    opt.add_inequality_constraint(myvconstraint, &data[1], 1e-8);

    // Set Tolerance
    opt.set_xtol_rel(1e-4);

    // Initial values
    std::vector<double> x(2);
    x[0] = 1.234; x[1] = 5.678;
    double minf;

    try{
        nlopt::result result = opt.optimize(x, minf);
        qDebug() << "Found minimum at f(" << x[0] << "," << x[1] << ") = " << minf;
    }
    catch(std::exception &e) {
        qDebug() << "nlopt failed: " << e.what();
    }

}



#endif // INVERSEKINEMATICS_H
