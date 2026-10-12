#include <iostream>
#include <cmath>
using namespace std;

int main() {
    const double eps = 0.0001;

    // a_n = lg(n!) * e^(-n*sqrt(n)); a_1 = lg(1!) = 0, тому починаємо з n = 2
    int n = 2;
    double lgFact = log10(2.0);             // lg(n!) через рекурентну формулу
    double a = lgFact * exp(-n * sqrt((double)n));
    double sum = 0;

    while (a >= eps) {
        sum += a;
        n++;
        lgFact += log10((double)n);         // lg(n!) = lg((n-1)!) + lg(n)
        a = lgFact * exp(-n * sqrt((double)n));
    }

    cout << "Сума ряду з точністю eps = " << eps << ": " << sum << endl;
    cout << "Кількість доданків: " << n - 2 << endl;
    return 0;
}
