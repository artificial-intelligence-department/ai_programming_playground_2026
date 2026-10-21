#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    const int N = 15; // Кількість членів ряду
    double sum = 0.0;

    // Оскільки для n = 1 ln(1) = 0 (ділення на 0),
    // сумуємо 15 членів ряду починаючи з n = 2 до n = 16
    for (int n = 2; n <= N + 1; ++n) {
        double term = pow(n, log(n)) / pow(log(n), n);
        sum += term;
    }

    cout << fixed << setprecision(4);
    cout << "Сума 15 членів ряду дорівнює: " << sum << endl;

    return 0;
}