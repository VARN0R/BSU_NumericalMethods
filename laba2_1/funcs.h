#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "../laba1/funcs.h"

using namespace std;

double my_function_1(double a, double b);

double my_function_2(double a, double b);

double derivative_f1_a(double a);

double derivative_f1_b(double b);

double derivative_f2_a(double a);

double derivative_f2_b(double b);

double calculate_vector_magnitude(vector<double> vec);

vector<double> my_newton_method(
    double initial_a,
    double initial_b,
    double epsilon_1,
    double epsilon_2,
    int max_iterations,
    double scaling_factor,
    vector<vector<double>> (&jacobian_calculator)(vector<double>, double)
);

vector<vector<double>> jacobian_calculator_1(vector<double> variables, double scaling_factor);

vector<vector<double>> jacobian_calculator_2(vector<double> variables, double scaling_factor);
