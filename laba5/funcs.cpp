#include "funcs.h"
#include <iostream>

double func1(const double& x) { 
    return exp(x/2) / sqrt(x+1); 
    }

double func2(const double& x, const double& y) { 
    return pow(x,2) + 2*y; 
}

double perform_intermediate_calculations_trapezoid(
        double (&fun)(const double&),
        const double& a, const double& b,
        const int& n) {
    double h = (b - a) / n;
    double mid_sum = 0;
    for (int i = 1; i < n - 1; i++) {
        mid_sum += fun(a + h * i);
    }

    return h * (fun(a) + 2 * mid_sum + fun(b)) / 2;
}

double solve_integral_trapezoid(double (&fun)(const double&),
                      const double& a, const double& b,
                      const double& eps) {
    int n = 10;
    double prev_integral_result = 0;
    double cur_integral_result = perform_intermediate_calculations_trapezoid(fun, a, b, n);

    while (abs(prev_integral_result - cur_integral_result) > 3 * eps) {
        n *= 2;
        prev_integral_result = cur_integral_result;
        cur_integral_result = perform_intermediate_calculations_trapezoid(fun, a, b, n);
    }

    return cur_integral_result;
}

double perform_intermediate_calculations_simpson(double (&fun)(const double &),
                                    const double &a, const double &b,
                                    const int &n) {

    int m = n / 2;
    double mid_sum1 = 0, mid_sum2 = 0;
    double h = (b - a) / n;

    for (int i = 1; i <= m; i++) {
        mid_sum1 += fun(a + h * double (2 * i - 1));
    }

    for (int i = 1; i <= m - 1; i++) {
        mid_sum2 += fun(a + h * double (2 * i));
    }

    return h * (fun(a) + 4 * mid_sum1 + 2 * mid_sum2 + fun(b)) / 3;
}


double solve_integral_simpson(double (&fun) (const double&),
                               const double& a, const double& b,
                               const double& eps) {
    int n = 10;
    double prev_integral_result = 0;
    double cur_integral_result = perform_intermediate_calculations_simpson(fun, a, b, n);

    while (abs(prev_integral_result - cur_integral_result) > 15 * eps) {
        n *= 2;
        prev_integral_result = cur_integral_result;
        cur_integral_result = perform_intermediate_calculations_simpson(fun, a, b, n);
    }

    return cur_integral_result;
}

double perform_intermediate_calculations_cubic_simpson(double (&fun)(const double &, const double&),
                                    const double &a, const double &b,
                                    const double &c, const double &d,
                                    int n) {

    int m = n / 2;
    n = 2 * m;
    double hx = (b - a) / (2 * n), hy = (d - c) / (2 * m);
    double result = 0;

    //int k = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
        
            //cout << k++ << endl;
            result += fun(a + double(2 * i) * hx, c + double(2 * j) * hy);
            result += 4 * fun(a + (double(2 * i - 1)) * hx, c + (double(2 * j)) * hy);
            result += fun(a + (double(2 * i + 2)) * hx, c + (double(2 * j)) * hy);
            result += 4 * fun(a + (double(2 * i)) * hx, c + (double(2 * j + 1)) * hy);
            result += 16 * fun(a + (double(2 * i + 1)) * hx, c + (double(2 * j + 1)) * hy);
            result += 4 * fun(a + (double(2 * i + 2)) * hx, c + (double(2 * j + 1)) * hy);
            result += fun(a + (double(2 * i)) * hx, c + (double(2 * j + 2)) * hy);
            result += 4 * fun(a + (double(2 * i + 1)) * hx, c + (double(2 * j + 2)) * hy);
            result += fun(a + (double(2 * i + 2)) * hx, c + (double(2 * j + 2)) * hy);
        }
    }

    return hx * hy * result / 9;
}

double solve_integral_cubic_simpson(double (&fun) (const double&, const double&),
                               const double& a, const double& b,
                               const double& c, const double& d,
                               const double& eps) {
    int n = 10;
    double prev_integral_result = 0;
    double cur_integral_result = perform_intermediate_calculations_cubic_simpson(fun, a, b, c, d, n);

    while (abs(prev_integral_result - cur_integral_result) > 15 * eps) {
        n *= 2;
        prev_integral_result = cur_integral_result;
        cur_integral_result = perform_intermediate_calculations_cubic_simpson(fun, a, b, c, d, n);
    }

    return cur_integral_result;
}