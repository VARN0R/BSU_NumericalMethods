#include "funcs.h"

int main() {
    bool isShowSteps;
    char ans;
    cout << "Should i show steps?[y/n]\n";
    cin >> ans;
    isShowSteps = (ans == 'y');

    vector<double> M{0.01, 0.05, 0.1};

    cout << "Jacobian method 1\n";
    vector<double> result = newtonMethod(1, 1, pow(10, -9), pow(10, -9), 1000,
                                         0, jacobian1, isShowSteps);
    if (!result.empty()) {
        cout << "Solution for x = (1, 1): ("
             << result[0] << ", " << result[1] << ")"
             << endl;
    }

    cout << "Jacobian method 2\n";

    for (int i = 0; i < 3; i++) {
        cout << "M = " << M[i] << endl;
        vector<double> result = newtonMethod(1, 1, pow(10, -9), pow(10, -9), 1000,
                                             M[i], jacobian2, isShowSteps);
        if (!result.empty()) {
            cout << "Solution for x = (1, 1): ("
                 << result[0] << ", " << result[1] << ")"
                 << endl;
        }
    }

    cout << "\n\nJacobian method 1\n";
    result = newtonMethod(2, 1.5, pow(10, -9), pow(10, -9), 1000, 0, jacobian1, isShowSteps);
    if (!result.empty()) {
        cout << "Solution for x = (2, 1.5): ("
             << result[0] << ", " << result[1] << ")"
             << endl;
    }

    cout << "Jacobian method 2\n";

    for (int i = 0; i < 3; i++) {
        cout << "M = " << M[i] << endl;
        result = newtonMethod(2, 1.5, pow(10, -9), pow(10, -9), 1000, M[i], jacobian2, isShowSteps);
        if (!result.empty()) {
            cout << "Solution for x = (2, 1.5): ("
                 << result[0] << ", " << result[1] << ")"
                 << endl;
        }
    }

    cout << "\n\nJacobian method 1\n";
    result = newtonMethod(-3, -1.5, pow(10, -9), pow(10, -9), 1000, 0,
                          jacobian1, isShowSteps);
    if (!result.empty()) {
        cout << "Solution for x = (-3, -1.5): ("
             << result[0] << ", " << result[1] << ")"
             << endl;
    }

    cout << "Jacobian method 2\n";

    for (int i = 0; i < 3; i++) {
        cout << "M = " << M[i] << endl;
        result = newtonMethod(-3, -1.5, pow(10, -9), pow(10, -9), 1000, M[i],
                              jacobian2, isShowSteps);
        if (!result.empty()) {
            cout << "Solution for x = (-3, -1.5): ("
                 << result[0] << ", " << result[1] << ")"
                 << endl;
        }
    }
    return 0;
}