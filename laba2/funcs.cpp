#include "funcs.h"

using namespace std;

double f1(double x1, double x2) {
    return pow(x1, 3) + pow(x2, 3) - 6 * x1 + 3;
}

double f2(double x1, double x2) {
    return pow(x1, 3) + pow(x2, 3) - 6 * x2 + 2;
}

double df1_dx1(double x1) {
    return 3 * pow(x1, 2) - 6;
}

double df1_dx2(double x2) {
    return 3 * pow(x2, 2);
}

double df2_dx1(double x1) {
    return 3 * pow(x1, 2);
}

double df2_dx2(double x2) {
    return 3 * pow(x2, 2) - 6;
}


double mod_vec(vector<double> x) {
    double sum = 0;
    for (double xk: x) {
        sum += xk * xk;
    }
    return sqrt(sum);
}

vector<double>
newtonMethod(
        double x1,
        double x2,
        double e1,
        double e2,
        int NIT,
        double M,
        vector<vector<double>> (&jacobian_calc)(vector<double>, double),
        bool isShowSteps
) {
    vector<double> result;
    vector<double> x {x1, x2};
    for (int k = 0; k < NIT; k++) {
        double res_f1k = f1(x[0], x[1]);
        double res_f2k = f2(x[0], x[1]);

        vector<vector<double>> jacobian = jacobian_calc(x, M);


        //J * dx = -F   we need to find dx
        //ветор невязки это по сути вектор решений F при xk
        vector<double> dx = solveLinearSystem({
            {jacobian[0][0], jacobian[0][1]},
            {jacobian[1][0], jacobian[1][1]}
            }, {-res_f1k, -res_f2k});


        if (dx.empty()) {
            double detJ = jacobian[0][0] * jacobian[1][1] - jacobian[0][1] * jacobian[1][0];
            if (isnan(detJ)) {
                cout << "det(J) is NAN, exiting\n";
                return result;
            }
            if (detJ == 0) {
                cout << "det(J) = 0, exiting\n";
                return result;
            }
            dx = {
                    (-jacobian[1][1] * res_f1k + jacobian[1][0] * res_f2k) / detJ,
                    (jacobian[0][1] * res_f1k + -jacobian[0][0] * res_f2k) / detJ
            };
            if (isnan(dx[0]) || isnan(dx[1])) {
                cout << "dx coordinates are too large to continue!\n";
                return result;
            }
        }
        double dx1k = dx[0];
        double dx2k = dx[1];

        double new_x1k = x[0] + dx1k;
        double new_x2k = x[1] + dx2k;

        double d1 = max(abs(res_f1k), abs(res_f2k));
        double d2;

        if (mod_vec({new_x1k, new_x2k}) < 1) {
            d2 = max(abs(x[0] - new_x1k), abs(x[1] - new_x2k));
        } else {
            d2 = max(
                    abs((x[0] - new_x1k) / new_x1k),
                    abs((x[1] - new_x2k) / new_x2k)
            );
        }

        if (isnan(d2)) {
            cout << "d2 is too large to continue!\n";
            return result;
        }

        if (d1 <= e1 && d2 <= e2) {
            result.push_back(new_x1k);
            result.push_back(new_x2k);
            return result;
        }
        if (isShowSteps) {
            cout << "Iteration no. " << k << " d1 = " << d1 << " d2 = " << d2
                 << endl;
        }

        x[0] = new_x1k;
        x[1] = new_x2k;
    }
    cout << "Iteration quantity overflow" << endl;
    return result;
}

vector<vector<double>> jacobian1(vector<double> x, double M) {
    vector<vector<double>> jacobian(2, vector<double>(2));
    jacobian[0][0] = df1_dx1(x[0]);
    jacobian[0][1] = df1_dx2(x[1]);
    jacobian[1][0] = df2_dx1(x[0]);
    jacobian[1][1] = df2_dx2(x[1]);
    return jacobian;
}

vector<vector<double>> jacobian2(vector<double> x, double M) {
    vector<vector<double>> jacobian;
    double f1_x = f1(x[0], x[1]);
    double f2_x = f2(x[0], x[1]);

    vector<double> dx(x);

    for (int i = 0; i < x.size(); i++) {
        dx[i] *= M;
    }

    vector<double> jacobian_row{
            (f1(x[0] + dx[0], x[1]) - f1_x) / dx[0],
            (f1(x[0], x[1] + dx[1]) - f1_x) / dx[1]
    };
    jacobian.push_back(jacobian_row);

    jacobian_row.clear();
    jacobian_row = {
            (f2(x[0] + dx[0], x[1]) - f2_x) / dx[0],
            (f2(x[0], x[1] + dx[1]) - f2_x) / dx[1]
    };
    jacobian.push_back(jacobian_row);

    return jacobian;
}