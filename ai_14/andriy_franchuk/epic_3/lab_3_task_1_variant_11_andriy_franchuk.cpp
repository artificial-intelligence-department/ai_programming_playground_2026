#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double sum_n(double x, int n);
double sum_e(double x, double eps);

int main(){
    const float a = 0.1;
    const float b = 1;
    const int k = 10;
    const int n = 10;
    const double eps = 0.0001;
    double x = 0;
    double Y, SN, SE = 0;

    for(int i = 0; i <= k; i++){
        x = ((b-a)/k)*i+a;

        Y = (1+2*pow(x, 2))*exp(pow(x, 2));
        SN = sum_n(x, n);
        SE = sum_e(x, eps);

        cout << "X: " << (double)x << " Y: " << (double)Y << " SN: " << (double)SN << " SE: " << (double)SE << endl;
    }

    return 0;
}
double sum_n(double x, int n){
    double term = 1;
    double S = term;
    for(int i = 0; i < n; i++){
        term *= (double)(2*i + 3) / ((2*i + 1)*(i + 1))*pow(x, 2);
        S += term;
    }
    return S;
}
double sum_e(double x, double eps){
    double term = 1;
    double S = term;
    int i = 0;
    while(abs(term) > eps){
        term *= (double)(2*i + 3) / ((2*i + 1)*(i + 1))*pow(x, 2);
        S += term;
        i++;
    }
    return S;
}