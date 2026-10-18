#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double a = 0.1; // початок інтервалу
    double b = 1; // кінець інтервалу
    int k = 10; // стала кількість розбитів
    double stp = (b-a)/k; // крок зміни х (0.09)

    int N = 10; // кк. членів для Sn
    double eps = 0.0001; // точність для Se

    for(int i = 0; i <= k; i++) {
        double x = a + i * stp;

        double Sn = 0;
        double a_N = 1; // перший член ряду
        for(int n = 0; n <= N; n++) {
            Sn += a_N;
            a_N *= (x*x) / ((2*n+1)*(2*n+2)); // наступний доданок за рекурсивною формулою
        }


        double Se = 0;
        double a_E = 1; // перший член ряду
        int n = 0;
        while(a_E >= eps) {
            Se += a_E;
            a_E *= (x*x) / ((2*n+1)*(2*n+2));
            n++;
        }

        double Y = (exp(x) + exp(-x)) / 2.0; // точне значення функції
        cout << fixed;
        cout << "X= " << x << " SN= " << Sn << " SE= " << Se << " Y= " << Y << endl;
    }
}    