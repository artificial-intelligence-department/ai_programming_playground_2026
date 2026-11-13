#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point { //зберігання координат вершини многокутника на площині
    double x, y;
};

int main() {

    int n; // к-сть вершин 
    if (!(cin >> n)) return 0;

    //статичні масиви  n <= 100)
    Point pts[105];
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
    }

    // Обчислення довжин сторін многокутника
    double L[105];
    for (int i = 0; i < n; ++i) {
        double dx = pts[(i + 1) % n].x - pts[i].x;
        double dy = pts[(i + 1) % n].y - pts[i].y;
        L[i] = sqrt(dx * dx + dy * dy);
    }

    if (n % 2 == 1) {
        // Для непарного n існує єдиний розв'язок
        double r[105];
        for (int i = 0; i < n; ++i) {
            double sum = 0;
            for (int j = 0; j < n; ++j) {
                double sign;
                if (j % 2 == 0) {
                sign = 1.0;  // Якщо індекс парний
                } else {
                sign = -1.0; // Якщо індекс непарний
                }
                sum += sign * L[(i + j) % n];
            }
            r[i] = sum / 2.0;
        }

        bool possible = true;
        for (int i = 0; i < n; ++i) {
            if (r[i] < -1e-7) {
                possible = false;
                break;
            }
        }

        if (!possible) {
            cout << -1 << endl;
        } else {
            double sum_sq = 0;
            for (int i = 0; i < n; ++i) {
                sum_sq += r[i] * r[i];
            }
            cout << fixed << setprecision(4) << sum_sq << endl;
        }
    } else {
        // Для парного n перевіряємо умову сумісності
        double alt_sum = 0;
        for (int j = 0; j < n; ++j) {
            double sign;
                if (j % 2 == 0) {
                sign = 1.0;
                } else {
                sign = -1.0;
                }
            alt_sum += sign * L[j];
        }

        if (abs(alt_sum) > 1e-7) {
            cout << -1 << endl;
            } else {
            // Рахуємо межі для першого радіуса
            double S[105];
            S[0] = 0;
            for (int k = 0; k < n; ++k) {
                double sign = (k % 2 == 0) ? 1.0 : -1.0;
                S[k + 1] = S[k] + sign * L[k]; // r_k = S_k + (-1)^k * r_0
            }

            double l_bound = 0.0;
            double u_bound = 1e18;

            for (int k = 0; k < n; ++k) {
                if (k % 2 == 0) {
                    double val = S[k];
                    if (val > l_bound) {
                        l_bound = val; 
                    }
                } else {
                    double val = S[k];
                    if (val < u_bound) {
                        u_bound = val; 
                    }
                }
            }

            if (l_bound > u_bound + 1e-7) {
                // Інтервал порожній — розв'язків немає
                cout << -1 << endl;
            } else if (abs(u_bound - l_bound) <= 1e-7) {
                // Рівно один розв'язок
                double r0 = l_bound;
                double r[105];
                r[0] = r0;
                for (int k = 0; k < n; ++k) {
                    r[(k + 1) % n] = L[k] - r[k];
                }
                double sum_sq = 0;
                for (int i = 0; i < n; ++i) {
                    sum_sq += r[i] * r[i];
                }
                cout << fixed << setprecision(4) << sum_sq << endl;
            } else {
                // Більше одного розв'язку
                cout << -2 << endl;
            }
        }
    }

    return 0;
}
