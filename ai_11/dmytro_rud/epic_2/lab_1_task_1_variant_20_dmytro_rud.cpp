#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;

//  (a+b)⁴ − (a⁴ + 4a³b)
//  ─────────────────────
//    6a²b² + 4ab³ + b⁴

float float_calculate() {
    // Створюємо всі змінні в одному місці
    float a = 100.0f;
    float b = 0.001f;
    float num_1 = 0.0f;
    float num_2 = 0.0f;
    float den_1 = 0.0f;
    float den_2 = 0.0f;
    float den_3 = 0.0f;

    float result_numerator = 0.0f;
    float result_denominator = 0.0f;

    // Рахуємо чисельник:
    // (a+b)⁴
    num_1 = powf(a + b, 4.0f);

    // (a⁴ + 4a³b)
    num_2 = powf(a, 4.0f) + 4.0f * powf(a, 3.0f) * b;

    // (a+b)⁴ − (a⁴ + 4a³b)
    result_numerator = num_1 - num_2;

    // Рахуємо знаменник:
    // 6a²b²
    den_1 = 6.0f * powf(a, 2.0f) * powf(b, 2.0f);

    // 4ab³
    den_2 = 4.0f * a * powf(b, 3.0f);

    // b⁴
    den_3 = powf(b, 4.0f);

    // 6a²b² + 4ab³ + b⁴
    result_denominator = den_1 + den_2 + den_3;

    // Рахуємо відповідь
    return result_numerator / result_denominator;
}

double double_calculate() {
    // Створюємо всі змінні в одному місці
    double a = 100.0;
    double b = 0.001;
    double num_1 = 0.0;
    double num_2 = 0.0;
    double den_1 = 0.0;
    double den_2 = 0.0;
    double den_3 = 0.0;
    double result_numerator = 0.0;
    double result_denominator = 0.0;

    // (a+b)⁴
    num_1 = pow(a + b, 4.0);

    // (a⁴ + 4a³b)
    num_2 = pow(a, 4.0) + 4.0 * pow(a, 3.0) * b;

    // (a+b)⁴ − (a⁴ + 4a³b)
    result_numerator = num_1 - num_2;

    // Рахуємо знаменник:
    // 6a²b²
    den_1 = 6.0 * pow(a, 2.0) * pow(b, 2.0);

    // 4ab³
    den_2 = 4.0 * a * pow(b, 3.0);

    // b⁴
    den_3 = pow(b, 4.0);

    // 6a²b² + 4ab³ + b⁴
    result_denominator = den_1 + den_2 + den_3;

    // Рахуємо відповідь
    return result_numerator / result_denominator;
}

int main() {
    // запускаємо розрахунки
    float float_result = float_calculate();
    double double_result = double_calculate();
    // Виводимо результати
    cout << "Результат float: " << setprecision(15) << float_result << endl;
    cout << "Результат double: " << setprecision(15) << double_result << endl;

    return 0;
}
