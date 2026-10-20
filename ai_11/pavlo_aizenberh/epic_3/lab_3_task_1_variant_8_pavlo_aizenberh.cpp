#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    const double PI  = acos(-1.0);
    const double a   = 0.1, b = 0.8;   // діапазон зміни x
    const int    k   = 10;             // кількість кроків
    const int    N   = 40;             // задане n
    const double eps = 0.0001;         // задана точність
    const double h   = (b - a) / k;    // крок

    cout << "Обчислення функції\n";
    cout << fixed << setprecision(6);

    for (int i = 0; i <= k; i++) {                 
        double x = a + i * h;

        double SN = 0, c = 1;                     
        for (int n = 1; n <= N; n++) {
            c *= x;                               
            SN += c * sin(n * PI / 4);            
        }

        double SE = 0; c = 1; int n = 0, cnt = 0;
        do {
            n++;
            c *= x;
            SE += c * sin(n * PI / 4);
            cnt = n;
        } while (c >= eps);

        // точне значення
        double Y = x * sin(PI / 4) / (1 - 2 * x * cos(PI / 4) + x * x);

        cout << "X=" << x << "  SN=" << SN << "  SE=" << SE << "  Y=" << Y << "   (доданків для eps: " << cnt << ")\n";
    }
}