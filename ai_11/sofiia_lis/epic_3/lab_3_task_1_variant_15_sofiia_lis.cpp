/* 
Епік 3. lab_3_task_1_variant_15
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

    double a = 0.1, b = 1;
    int k = 10;
    double step = (b - a) / k;
    double eps = 0.0001;

    for(double x = a; x <= b; x += step) {
        double S_n = 0;
        double c_n = -x;    //чисельник при n=0 
        for(int n = 1; n <= 30; n++) {
            c_n = c_n * (- pow(x, 2));
            S_n += c_n / (4 * pow(n, 2) - 1);
        }

        int n = 1;
        double S_eps = 0;
        double c_eps = -x;  // чисельник при n=0
        double r_eps = c_eps / (-1);    // доданок при n=0

        while(fabs(r_eps) >= eps) {
            c_eps = c_eps * (- pow(x, 2));
            r_eps = c_eps / (4 * pow(n, 2) - 1);
            S_eps += r_eps;
            n ++;
        }

        double y = (1 + pow(x, 2)) * atan(x) / 2 - x / 2;

        cout << "X = " << left << setw(6) << x << " SN = " << left << setw(11) << S_n << " SE = " << left << setw(12) << S_eps << " Y = " << y << endl;

    }

    return 0;
}