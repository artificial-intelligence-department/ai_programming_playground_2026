#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main(){
    double x_min = 0.1;
    double x_max = 1;
    double x=x_min;
    double k = (x_max-x_min)/10;
    double eps = 0.0001;
    cout << "Обчислення функції"<< endl;
    for (int j=0; j<=10; j++) {
        double sum_n = x;
        double sum_e = x;
        double a_current = x;
        for (int n = 0; n<20; n++) {
            a_current = a_current*x*x/(4*n*n+10*n+6);
            sum_n+=a_current;
        }
        a_current = x;
        int n = 0;
        while (a_current >= eps) {
            a_current = a_current*x*x/(4*n*n+10*n+6);
            sum_e+=a_current;
            n++;
        }
        double y =( exp(x)-exp(-x))/2;
        cout << fixed << setprecision(6);
        cout << "X=" << x << "\tSN="<< sum_n << "\tSE="<< sum_e << "\tY=" << y <<endl;
        x+=k;
    }
    
}