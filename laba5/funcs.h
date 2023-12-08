#pragma once

#include <cmath>

using namespace std;

double func1(const double& x);
double func2(const double& x, const double& y);

double perform_intermediate_calculations_trapezoid(
        double (&fun)(const double&),
        const double& a, const double& b,
        const int& n);

double solve_integral_trapezoid(double (&fun)(const double&),
                      const double& a, const double& b,
                      const double& eps);

double perform_intermediate_calculations_simpson(double (&fun)(const double &),
                                    const double &a, const double &b,
                                    const int &n);

double solve_integral_simpson(double (&fun) (const double&),
                               const double& a, const double& b,
                               const double& eps);

double solve_integral_cubic_simpson(double (&fun) (const double&, const double&),
                               const double& a, const double& b,
                               const double& c, const double& d,
                               const double& eps);

double perform_intermediate_calculations_cubic_simpson(double (&fun)(const double &, const double&),
                                    const double &a, const double &b,
                                    const double &c, const double &d,
                                    int n);