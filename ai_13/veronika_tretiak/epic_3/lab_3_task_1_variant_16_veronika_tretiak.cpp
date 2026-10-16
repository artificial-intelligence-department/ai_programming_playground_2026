#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    const double eps = 0.0001;
    const int n = 40;
    const int k = 10;
    const double a = acos(-1.0) / 5.0;
    const double b =  acos(-1.0);
    const double m = (b - a) / k;

    cout  << fixed << setprecision(6) << endl;
    for (int i = 0; i <= k; i++){
        double x = a + i * m;

        double SN = 0.0;
        for (int j = 1; j<= n; j++){
            double trm = cos((2 * j - 1) * x) / pow(2 * j - 1, 2);
            SN += trm;
        }

        double SE = 0.0;
        int j = 1;
        double trm;
        do{
            trm = cos((2 * j - 1) * x) / pow(2 * j - 1, 2);
            SE+= trm;
            j++;
        } 
        while (1.0 / pow(2 * j - 1, 2) >= eps );
        double Y = acos(-1.0) * acos(-1.0) / 8.0 - acos(-1.0) * fabs(x) / 4.0;

        cout << "X = " << setw(10) << x << "  SN = " << setw(10) << SN << "  SE = " << setw(10) << SE << "  Y = " << setw(10) << Y << endl;

    }
    return 0;
}