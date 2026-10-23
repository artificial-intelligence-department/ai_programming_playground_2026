/*
  Назва задачі: Lab 3 Task 1
  Варіант: 7
  Автор: Лисюк Андріана
  Група: ШІ-13
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
   const double a = 0.1, b = 1.0;
   const double eps = 0.0001; 
   const int k = 10;
   const int n = 10;
   double h = (b - a) / k;

   cout << "Обчислення функції" << endl;

   for (int i = 0; i <= k; i++) {
        double  x = a + i * h;
        double an = 1.0;
        double sn = an;
        for (int j = 0; j <= n; j++){
            an = an * (-x * x) / ((2 * j + 1) * (2 * j + 2));
            sn += an;
        }

        double t = 1.0;
        double se = 0.0;
        int m = 0;
        while (fabs(t) >= eps) {
            se += t;
            t = t * (-x * x) / ((2 * m + 1) * (2 * m + 2));
            m++;
        }
        double y = cos(x);

        cout << fixed << setprecision(6) << "X=" << x << "  SN=" << sn << "  SE=" << se << "  Y=" << y << endl;
    }

    return 0;
}
