#include "funcs.h"

using namespace std;

double my_function_1(double a, double b) {
    return pow(a, 3) + pow(b, 3) - 6 * a + 3;
}

double my_function_2(double a, double b) {
    return pow(a, 3) + pow(b, 3) - 6 * b + 2;
}

double derivative_f1_a(double a) {
    return 3 * pow(a, 2) - 6;
}

double derivative_f1_b(double b) {
    return 3 * pow(b, 2);
}

double derivative_f2_a(double a) {
    return 3 * pow(a, 2);
}

double derivative_f2_b(double b) {
    return 3 * pow(b, 2) - 6;
}

double calculate_vector_magnitude(vector<double> vec) {
    double sum = 0;
    for (double elem : vec) {
        sum += elem * elem;
    }
    return sqrt(sum);
}

vector<double> my_newton_method(
    double initial_a,
    double initial_b,
    double epsilon_1,
    double epsilon_2,
    int max_iterations,
    double scaling_factor,
    vector<vector<double>> (&jacobian_calculator)(vector<double>, double)
) {
    vector<double> result;
    vector<double> variables{initial_a, initial_b};
    
    for (int k = 0; k < max_iterations; k++) {
        double f1_result = my_function_1(variables[0], variables[1]);
        double f2_result = my_function_2(variables[0], variables[1]);

        vector<vector<double>> jacobian_matrix = jacobian_calculator(variables, scaling_factor);

        vector<double> solution = solveLinearSystem({
            {jacobian_matrix[0][0], jacobian_matrix[0][1]},
            {jacobian_matrix[1][0], jacobian_matrix[1][1]}
        }, {-f1_result, -f2_result});

        if (solution.empty()) {
            double determinant = jacobian_matrix[0][0] * jacobian_matrix[1][1] - jacobian_matrix[0][1] * jacobian_matrix[1][0];
            if (isnan(determinant)) {
                cout << "det(J) is NAN, exiting\n";
                return result;
            }
            if (determinant == 0) {
                cout << "det(J) = 0, exiting\n";
                return result;
            }

            solution = {
                (-jacobian_matrix[1][1] * f1_result + jacobian_matrix[1][0] * f2_result) / determinant,
                (jacobian_matrix[0][1] * f1_result + -jacobian_matrix[0][0] * f2_result) / determinant
            };

            if (isnan(solution[0]) || isnan(solution[1])) {
                cout << "Solution coordinates are too large to continue!\n";
                return result;
            }
        }

        double delta_a = solution[0];
        double delta_b = solution[1];

        double new_a = variables[0] + delta_a;
        double new_b = variables[1] + delta_b;

        double d1 = max(abs(f1_result), abs(f2_result));
        double d2 = max(abs(variables[0] - new_a), abs(variables[1] - new_b));

        if (isnan(d2)) {
            cout << "d2 is too large to continue!\n";
            return result;
        }

        if (d1 <= epsilon_1 && d2 <= epsilon_2) {
            result.push_back(new_a);
            result.push_back(new_b);
            return result;
        }

        variables[0] = new_a;
        variables[1] = new_b;
    }

    cout << "Iteration quantity overflow" << endl;
    return result;
}

vector<vector<double>> jacobian_calculator_1(vector<double> variables, double scaling_factor) {
    vector<vector<double>> jacobian(2, vector<double>(2));
    jacobian[0][0] = derivative_f1_a(variables[0]);
    jacobian[0][1] = derivative_f1_b(variables[1]);
    jacobian[1][0] = derivative_f2_a(variables[0]);
    jacobian[1][1] = derivative_f2_b(variables[1]);
    return jacobian;
}

vector<vector<double>> jacobian_calculator_2(vector<double> variables, double scaling_factor) {
    vector<vector<double>> jacobian_matrix;
    double f1_result = my_function_1(variables[0], variables[1]);
    double f2_result = my_function_2(variables[0], variables[1]);

    vector<double> delta_x(variables);

    for (int i = 0; i < variables.size(); i++) {
        delta_x[i] *= scaling_factor;
    }

    vector<double> jacobian_row{
        (my_function_1(variables[0] + delta_x[0], variables[1]) - f1_result) / delta_x[0],
        (my_function_1(variables[0], variables[1] + delta_x[1]) - f1_result) / delta_x[1]
    };
    jacobian_matrix.push_back(jacobian_row);

    jacobian_row.clear();
    jacobian_row = {
        (my_function_2(variables[0] + delta_x[0], variables[1]) - f2_result) / delta_x[0],
        (my_function_2(variables[0], variables[1] + delta_x[1]) - f2_result) / delta_x[1]
    };
    jacobian_matrix.push_back(jacobian_row);

    return jacobian_matrix;
}
