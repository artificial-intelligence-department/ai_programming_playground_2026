#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
int main() {
    double a = 0.1, b = 0.8, k = 10.0; 
    int n = 40;
    double step = (b - a) / k;
    for (double x = a ; x < b + step; x += step) {
        double sn = 0.0;
        double y = (x * sin (M_PI / 4))/(1 - 2 * x * cos (M_PI / 4) + x * x);
        for (int j = 1; j <= n; ++j) { 
            sn += pow(x, j) * sin(j * (M_PI / 4));
        }
        double se = 0.0;
        int i = 1;
        double e = 0.0001;
        
        while (abs(pow(x, i)) >= e) {
            se += pow(x, i) * sin(i * (M_PI / 4));
            i++;
        }
        cout << "x = " << x << "," << "\t" << "sn = " << fixed << setprecision(4)<< sn << "\t" << "se = "<< fixed << setprecision(4) << se  << "\t" << fixed << setprecision(4)<< "y = " << y << "\n";
    }
}