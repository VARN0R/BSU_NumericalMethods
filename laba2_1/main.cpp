#include "funcs.h"

int main() {
    vector<double> M{0.01, 0.05, 0.1};

    cout << "1-st jacobian method ";
    cout << endl;
       
    vector<double> result1 = my_newton_method(1, 1, pow(10, -9), pow(10, -9), 1000,
                                              0, jacobian_calculator_1);
    if (!result1.empty()) {
        cout << "solution - (" << result1[0] << ", " << result1[1] << ")" << endl;
    }

    cout << "2-end jacobian method";
    cout << endl;

    for (int i = 0; i < 3; i++) {
        cout << "M = " << M[i] << endl;
        vector<double> result2 = my_newton_method(1, 1, pow(10, -9), pow(10, -9), 1000,
                                                  M[i], jacobian_calculator_2);
        if (!result2.empty()) {
            cout << "solution - (" << result2[0] << ", " << result2[1] << ")" << endl;
        }
    }

    cout << "1-st jacobian method";
    cout << endl;
    vector<double> result3 = my_newton_method(2, 1.5, pow(10, -9), pow(10, -9), 1000, 0, jacobian_calculator_1);
    if (!result3.empty()) {
        cout << "solution - (" << result3[0] << ", " << result3[1] << ")" << endl;
    }

    cout << "2-end jacobian method";
    cout << endl;

    for (int i = 0; i < 3; i++) {
        cout << "M = " << M[i] << endl;
        vector<double> result4 = my_newton_method(2, 1.5, pow(10, -9), pow(10, -9), 1000, M[i], jacobian_calculator_2);
        if (!result4.empty()) {
            cout << "solution - (" << result4[0] << ", " << result4[1] << ")" << endl;
        }
    }

    cout << "1-st jacobian method";
    cout << endl;
    vector<double> result5 = my_newton_method(-3, -1.5, pow(10, -9), pow(10, -9), 1000, 0, jacobian_calculator_1);
    if (!result5.empty()) {
        cout << "solution - (" << result5[0] << ", " << result5[1] << ")" << endl;
    }

    cout << "2-end jacobian method";
    cout << endl;

    for (int i = 0; i < 3; i++) {
        cout << "M = " << M[i] << endl;
        vector<double> result6 = my_newton_method(-3, -1.5, pow(10, -9), pow(10, -9), 1000, M[i], jacobian_calculator_2);
        if (!result6.empty()) {
            cout << "solution - (" << result6[0] << ", " << result6[1] << ")" << endl;
        }
    }

    return 0;
}
