#include <iostream>

#include "funcs.h"

using namespace std;

int main() {

    cout << "Метод трапеций при eps = 1e-4:" << endl;
        cout << solve_integral_trapezoid(func1, 0.0, 1.047, 1e-4)
        << endl;
    cout << "Метод трапеций при eps = 1e-5:" << endl;
        cout << solve_integral_trapezoid(func1, 0.0, 1.047, 1e-5)
        << endl;

    cout << endl;

    cout << "Метод Симпсона при eps = 1e-4:" << endl;
        cout << solve_integral_simpson(func1, 0.0, 1.047, 1e-4)
        << endl;
    cout << "Метод Симпсона при eps = 1e-5:" << endl;
        cout << solve_integral_simpson(func1, 0.0, 1.047, 1e-5)
        << endl;

    cout << endl;

    cout << "Кубический метод при eps = 1e-4:" << endl;
        cout << solve_integral_cubic_simpson(
                func2, 0.0,
                2.0, 0.0,
                1.0, 1e-4
            )
        << endl;
    cout << "Кубический метод при eps = 1e-5:" << endl;
        cout << solve_integral_cubic_simpson(
                func2, 0.0,
                2.0, 0.0,
                1.0, 1e-5
            )
        << endl;

    cout << endl;
}
