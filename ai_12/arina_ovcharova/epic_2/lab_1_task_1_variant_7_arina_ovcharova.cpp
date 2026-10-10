#include <iostream>
#include <iomanip>

using namespace std;

// Lab 1, Task 1 (варіант 7):
// ((a - b)^3 - a^3) / (b^3 - 3ab^2 - 3a^2b) при a = 1000, b = 0.0001
// Обчислення виконується для float та double з проміжними змінними.
int main() {
    const float af = 1000.0f;
    const float bf = 0.0001f;

    // Обчислення для типу float з використанням проміжних змінних.
    const float a_minus_b_f = af - bf;
    const float a_cubed_f = af * af * af;
    const float b_cubed_f = bf * bf * bf;
    const float b_squared_f = bf * bf;
    const float numerator_f = a_minus_b_f * a_minus_b_f * a_minus_b_f - a_cubed_f;
    const float denominator_f = b_cubed_f - 3.0f * af * b_squared_f
                              - 3.0f * af * af * bf;
    const float result_f = numerator_f / denominator_f;

    const double ad = 1000.0;
    const double bd = 0.0001;

    // Обчислення для типу double з використанням проміжних змінних.
    const double a_minus_b_d = ad - bd;
    const double a_cubed_d = ad * ad * ad;
    const double b_cubed_d = bd * bd * bd;
    const double b_squared_d = bd * bd;
    const double numerator_d = a_minus_b_d * a_minus_b_d * a_minus_b_d - a_cubed_d;
    const double denominator_d = b_cubed_d - 3.0 * ad * b_squared_d
                               - 3.0 * ad * ad * bd;
    const double result_d = numerator_d / denominator_d;

    cout << fixed << setprecision(12);
    cout << "Lab 1 Task 1, variant 7\n";
    cout << "a = 1000, b = 0.0001\n\n";
    cout << "float:\n";
    cout << "  numerator   = " << numerator_f << '\n';
    cout << "  denominator = " << denominator_f << '\n';
    cout << "  result      = " << result_f << "\n\n";

    cout << "double:\n";
    cout << "  numerator   = " << numerator_d << '\n';
    cout << "  denominator = " << denominator_d << '\n';
    cout << "  result      = " << result_d << '\n';

    return 0;
}
