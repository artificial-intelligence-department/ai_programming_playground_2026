#include <iostream>
#include <cmath>
using namespace std;
int main() {
    double a = 0.2, b = 1.0;
    int k = 10, n = 10;
    double h = (b-a)/k;
    for (int i = 0; i<=k; i++) {
        double x = a+i*h;
        double y = 0.5 * log(x);
        double sumN = 0;
        double t = (x-1) / (x+1);
        for (int j = 0; j <= n; j++) {
            sumN += pow(t, 2*j+1) / (2*j+1);
        }
        double sumE = 0;
        double precision = 0.0001;
        double term = t;
        int j = 0;
        while (fabs(term) >= precision) {
            sumE += term;
            j++;
            term = pow(t, 2*j+1) / (2*j+1);
        }
        cout << "x = " << x << " y = " << y << " sumN = " << sumN << " sumE = " << sumE << endl;



    }
    return 0;
}

