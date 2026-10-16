#include <iostream>
#include <cmath>

using namespace std;

int main(){
    const double a = 0.2;
    const double b = 1.;
    const double epsilon = 0.0001;
    double x = a;
    int n;

    cout << "Введіть значення n:";
    cin >> n;

    while(x<=b){
        double t = (x-1)/(x+1);
        double term = t;
        double sum = term;

        cout << "X=" << x;

        for(int i = 0; i <= n; i++){
            term *= (2.*i+1.)/(2.*i+3.) * t * t;
            sum += term;
        }

        cout << "   SN=" << sum;

        term = t;
        sum = term;
        int j = 0;

        while(abs(term) > epsilon){
            term *= (2.*j+1.)/(2.*j+3.) * t * t;
            sum += term;
            j++;
        }

        cout << "   SE=" << sum << "   Y=" << 0.5*log(x) << endl;

        x += 0.08;
    }


    return 0;
}