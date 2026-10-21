#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double a = 0.1;
    double b = 1.0;
    int k = 10;
    double c = (b - a) / k;
    int n = 10;
    double eps = 0.0001;

    cout << "             Обчислення функції" << endl;
    for (double x = a; x <= b; x += c ){
        double SN = 1;
        double elementN = 1.0;
        for( int j = 1; j <= n; j++){
            elementN = elementN * ((2.0 * j + 1.0)/ (2.0 * j - 1.0)) * (pow(x,2) / j) ; 
            SN += elementN;
        }
        double SE = 0.0;
        double elementE = 1.0;
        int j = 1;
        while(fabs(elementE) >= eps){
            SE += elementE;
            elementE = elementE * ((2.0 * j + 1.0)/ (2.0 * j - 1.0)) * (pow(x,2) / j);
            j++;
        }
        double Y = (1.0 + 2 * pow(x, 2)) * exp(pow(x, 2));
        cout << setw(10) << "X= "  << setw(10) << "SN= " << setw(10) << "SE= " << setw(10) << "Y= " << endl;
        cout << fixed << setprecision(6) << setw(10) << x << setw(10) << SN << setw(10) << SE << setw(10) << Y << endl;

    }
    return 0;
}