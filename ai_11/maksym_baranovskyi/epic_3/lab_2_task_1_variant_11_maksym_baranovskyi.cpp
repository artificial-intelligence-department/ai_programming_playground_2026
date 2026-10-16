#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){

    const double epsilon = 0.0001;
    int n = 1.0;
    double sum = 0;
    double term = 1.0;

    while(term > epsilon){
        sum += term;
        term = term * pow((n / (n+ 1.0)), n);
        
        n++;
    }

    cout << fixed << setprecision(4) << "Сума ряду (n!/n^n) з точністю eps = " << epsilon << ", дорівнює: " << sum << endl;

    return 0;
}