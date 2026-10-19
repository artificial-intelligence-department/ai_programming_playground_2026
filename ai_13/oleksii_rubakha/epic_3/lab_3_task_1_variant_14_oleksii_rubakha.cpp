
/*
    Lab 3 - Task 1, Рубаха Олексій, ШІ-13, варіант 14
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/*
Функція: y = 1/4 * (x^2 - PI^2/3)
Сума ряду: S = -cos(x) + cos(2x)/2^2 - ... + (-1)^n*cos(nx)/n^2
Діапазон: PI/5 <= x <= PI
*/

int main() {
    // Константи для обчислень
    const double EPSILON = 0.0001;        // Задана точність для обчислення SE
    const double PI = acos(-1.0);         // Значення числа Пі
    const double X_MIN = PI / 5;          // Початок діапазону x
    const double X_MAX = PI;              // Кінець діапазону x

    // Параметри циклу та розбиття
    const int FIXED_TERMS_COUNT = 20;     // Кількість членів ряду для SN (n)
    const int STEPS_COUNT = 10;           // Кількість кроків розбиття діапазону (k)
    
    double current_x = X_MIN;

    // Головний цикл для проходження по діапазону від X_MIN до X_MAX
    while (current_x <= X_MAX + 0.000001) {
        
        // 1. Обчислення суми перших N членів ряду (SN)
        double sum_n_terms = 0;
        for (int i = 1; i <= FIXED_TERMS_COUNT; i++) {
            double current_term = pow(-1, i) * cos(i * current_x) / (i * i);
            sum_n_terms += current_term;
        }

        // 2. Обчислення суми ряду з точністю EPSILON (SE)
        double sum_precision_terms = 0;
        int i = 1;
        while (true) {
            double current_term = pow(-1, i) * cos(i * current_x) / (i * i);
            sum_precision_terms += current_term;

            // Якщо модуль поточного члена став меншим за точність, зупиняємо цикл
            if (fabs(current_term) < EPSILON) {
                break;
            }
            i++;
        }

        // 3. Розрахунок аналітичного значення функції за формулою
        double analytical_value = (current_x * current_x - PI * PI / 3) / 4;

        // Виведення результатів з точністю до 6 знаків після коми
        cout << fixed << setprecision(6)
             << "X = " << current_x
             << " | SN = " << sum_n_terms
             << " | SE = " << sum_precision_terms
             << " | F = " << analytical_value << endl;

        // Збільшення x на величину одного кроку
        current_x = current_x + (X_MAX - X_MIN) / STEPS_COUNT;
    }

    return 0;
}