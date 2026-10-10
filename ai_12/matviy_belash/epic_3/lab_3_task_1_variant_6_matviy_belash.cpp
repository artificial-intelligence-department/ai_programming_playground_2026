#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){

    double h = 0.09;
    long double sum = 1;
    long double sum_e = 1;
    long double x = 0.1;
    long double a = 0;
    long double y = 0;
    const double E = 0.0001;
    const double p = 3.14159265358979323846;
    const double e = 2.71828182845904523536;
    double fact = 1;
    long double t; 

    for(x; x <= 1; x += h){

        sum = 1;
        sum_e = 1;
        fact = 1;

        a = (sqrt(2) / 2.0) * x; //перший член суми (після 1) тому наступний цикл рахує одразу другий
        for(int n = 2; n <= 25; n++){
            sum += a;   
            fact *= n;
            a = (cos(n * (p/4)) / fact) * pow(x, n);
        }
        sum += a; //додаємо 25 елемент до суми 
        fact = 1;

        int n = 2;
        a = (sqrt(2) / 2.0) * x;   
        do{
            fact *= n;                     
            t = pow(x, n) / fact;          
            sum_e += t * cos(n * (p/4));  
            n++;
        }while(t >= E);
        sum_e += a;

        y = pow(e, (x * cos(p/4.0))) * cos(x * sin(p/4.0));

        cout << left;
        cout << "X=" << setw(4) << x << "  SN=" << setw(7) <<  sum << "  SE=" << setw(7) << sum_e << "  Y=" << setw(7) << y << endl; 
    }
}
