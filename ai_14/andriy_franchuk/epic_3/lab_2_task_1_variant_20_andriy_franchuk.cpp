#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(){
    int n = 0;
    double eps = 0.0001;
    double b, c, term, sum = 0;
    do{
        b = exp(n);
        c = pow(100, -pow(n, 2));
        term = b * c;
        sum += term;
        n++;
    }while(fabs(term) > eps);

    cout.precision(10);

    cout << "Результат: " << sum << endl;

    return 0;
}