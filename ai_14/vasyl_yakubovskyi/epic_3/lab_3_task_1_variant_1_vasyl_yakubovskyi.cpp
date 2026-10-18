/*
Task: lab 3 task 1 option 1
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/


#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;



int main (){
    
    setlocale(LC_ALL, "uk_UA");

    const double eps = 0.0001;
    double a = 0.1;
    double b = 1.0;
    double k = 10.0;
    double step = (b - a) / k;
    double x = 0.1;
    
    cout << "==================== ОБЧИСЛЕННЯ ФУНКЦІЇ ===================" << endl;
    while( x <= 1){

        double y_exact = 0;
        y_exact = pow(3.0, x);


        double a1 = 1.0;
        double sum1 = 0;
        
        for(double n = 0; n < 10; n++){
                sum1 += a1;
                a1 = a1* ((log(3.0)*x) / (n+1));

        }
        double n = 0;
        double a2 = 1.0;
        double sum2 = 0;
        while(a2 >= eps){
                sum2 += a2;
                a2 = a2* ((log(3.0)*x) / (n+1));
                n++;
            }


        cout << fixed << setprecision(2) << "X = " << x << "\t"
             << setprecision(5) 
             << "SN = " << sum1 << "\t"
             << "SE = " << sum2 << "\t"
             << "Y = " << y_exact << endl;

        x += step;

    }

    return 0;
}