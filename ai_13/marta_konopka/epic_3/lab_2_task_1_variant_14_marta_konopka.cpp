#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double eps = 0.0001;
    double a = 1.0 / 3.0;
    double sum = 0.0;
    double n = 1.0;

    while(a >= eps){
        sum += a; 
        a = a * pow(n / (n + 1), n);
        n++ ; 
    }
    cout << " Обчислення суми ряду з точністю ε=0.0001, загальний член якого an = n! / 3n^n:  " << fixed << setprecision(6) << sum << endl;
    return 0;
}
