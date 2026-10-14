#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << fixed << setprecision(4);

    const double epsilon = 0.0001;
    double a = 0.5; //a_1 при n=1
    double sum = 0.0;
    int n = 1;

    while (a > epsilon) {
        sum += a;
        n++;
        a = a / ((3.0 * n - 1.0) * (3.0 * n - 2.0));
    }

    cout << "=======================================\n";
    cout << "   ОБЧИСЛЕННЯ СУМИ НЕНОРМОВАНОГО РЯДУ  \n";
    cout << "=======================================\n";
    cout << "Точність (epsilon): " << epsilon << endl;
    cout << "Кількість доданих членів ряду: " << n - 1 << endl;
    cout << "Загальна сума ряду: " << sum << endl;
    cout << "=======================================\n";
    return 0;
}
