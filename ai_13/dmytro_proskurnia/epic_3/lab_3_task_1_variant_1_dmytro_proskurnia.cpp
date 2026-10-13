/*
Lab_3_task_1
Проскурня Дмитро ШІ-13 варіант 8
*/
#include <iostream>
#include <iomanip>
#include <cmath>

using ldouble = long double;

int main() {
    const int n = 40;
    const ldouble a = 0.1L;
    const ldouble b = 0.8L;
    const ldouble step = (b - a) / 10.0L;
    const ldouble PI = std::acos(-1.0L);

    //модифікуємо код так щоб k було додатнє для того щоб позбутися проблем з точністю
    for (int k = 0; k <= 10; k++) {
        const ldouble x = a + k * step;
        ldouble sum_n{};
        for (int i = 1; i <= n; i++) {
            ldouble t = std::pow(x, i) * (std::sin(i * PI / 4.0L));
            sum_n += t;
        }

        const ldouble eps = 0.0001L;
        ldouble sum_eps{};
        for (int i = 1; ; i++) {
            ldouble t = std::pow(x, i) * (std::sin(i * PI / 4.0L));

            //викоричтовуємо тільки x^i тому що сінус може дорівнювати 0,
            //через що разрахунки будуть не точними
            if (std::abs(std::pow(x, i)) < eps) {
                break;
            }

            sum_eps += t;
        }

        std::cout << std::defaultfloat
                  << "x                                        = " << x << "\n";
        std::cout << std::fixed << std::setprecision(4)
                  << "f(x) при розкладі у степеневий ряд з n   = " << sum_n << std::endl;
        std::cout << std::fixed << std::setprecision(4)
                  << "f(x) при розкладі у степеневий ряд з eps = " << sum_eps << std::endl;
        std::cout << std::fixed << std::setprecision(4)
                  << "f(x)                                     = "
                  << (x * std::sin(PI / 4.0L)) / (1.0L - 2.0L * x * std::cos(PI / 4.0L) + x * x);
        std::cout << std::endl << std::endl;
    }

    return 0;
}
