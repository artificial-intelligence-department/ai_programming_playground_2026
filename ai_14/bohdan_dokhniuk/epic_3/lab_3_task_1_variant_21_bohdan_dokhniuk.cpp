/*  
Lab 3 Task 1
Дохнюк Богдан 
ШІ-14
Варіант 21 
*/

#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const double a = 0.1;
    const double b = 1.0;
    const int k = 10;
    const int n = 40;
    const double eps = 0.0001;
    const double h = (b - a) / k;

    cout << fixed << setprecision(6);
    cout << "Обчислення функції arctg(x)\n";
    cout << "X\t\tSN\t\tSE\t\tY\n";

    for (int j = 0; j <= k; j++) {
        double x = a + j * h;

        double an = x;
        double SN = 0.0;
        for (int i = 0; i < n; i++) {
            SN = SN + an;
            an = -an * x * x * (2 * i + 1) / (2 * i + 3);
        }

        an = x;
        double SE = 0.0;
        int i = 0;
        while (true) {
            if (fabs(an) < eps) {
                break;
            }
            SE = SE + an;
            an = -an * x * x * (2 * i + 1) / (2 * i + 3);
            i++;
        }

        double Y = atan(x);
        cout << x << "\t" << SN << "\t" << SE << "\t" << Y << endl;
    }

    return 0;
}
