#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double factorial(int n)
{
    double c = 1;
    for (int i = 0; i < n; i++){
        c *= (n-i);
    }
    return c;
}

int main()
{
    const int n = 10;
    double eps = 0;
    cin >> eps; 
    double a = 0;
    double x[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};
    for (int i = 0; i < size(x); i++){
        double SN = 0;
        int k = 0;
        for (int j = 0; j < n; j++){
            a = pow((-1),k)*pow(x[i], (2*k+1))/factorial(2*k+1);
            SN += a;
            k++;
        }
        double b = x[i];
        double Seps = b;
        int q = 0;
        while (abs(b) > eps){
            b = (b*(-1)*x[i]*x[i])/((2*q+3)*(2*q+2));;
            Seps += b;
            q++;
        }
        double y = sin(x[i]);
        cout << "X = " << fixed << setprecision(5) << x[i] << " " << "SN = " << SN << " " << "Seps = " << Seps << " " << "Y = " << y << endl;
    }
}