#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    const double PI = acos(-1.0);
    const double a = PI / 5;      
    const double b = PI;          
    const int k = 10;             
    const double h = (b - a) / k; // крок
    const int n = 40;             
    const double eps = 0.0001;    //точність

    cout << "Обчислення функції" << endl;
    cout << fixed << setprecision(6);

    for (int i = 0; i <= k; i++) {
        double x = a + i * h;

        double SN = 0;
        for (int j = 1; j <= n; j++) {
            int m = 2 * j - 1;
            SN += cos(m * x) / (m * (double)m);
        }

        double SE = 0;
        int j = 1;
        int m = 1;
        double term = cos(x);   // перший доданок
        while (1.0 / (m * (double)m) >= eps) {
            SE += term;
            j++;
            m = 2 * j - 1;
            term = cos(m * x) / (m * (double)m);
        }

        // точне значення функції
        double Y = PI * PI / 8 - PI / 4 * fabs(x);

        cout << "X=" << x << "  SN=" << SN
             << "  SE=" << SE << "  Y=" << Y << endl;
    }

    return 0;
}