#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    double epsilon = 0.0001;
    double term_1 = 1. / 2.;
    double term_2 = 1. / 3.;
    double term = term_1 + term_2;
    double sum = term_1 + term_2;
    int n = 1;

    while(abs(term) > epsilon){
        term_1 = term_1 * 1./2.;
        term_2 = term_2 * 1./3.;
        term = term_1 + term_2;
        sum += term;
        n++;
    }

    cout << "Cумa ряду з точністю ε=0.0001, загальний член якого a_n = 1/2^n + 1/3^n дорівнює:" << fixed << setprecision(4) << sum << endl;

    return 0;
}