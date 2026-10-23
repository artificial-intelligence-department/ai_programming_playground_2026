/*
Назва: Алабораторна робота 3 Варіант 22
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main (){
    const double a = 0.1;
    const double b=1.0;
    const double k=10.0;
    const double h = (b-a)/k;
    const int n_max=35;
    const double e = 0.0001;
    double x;
    cout << fixed << setprecision(5);
    for (int i=0; i<=10; i++){
        x = a + i*h;
        double Y = (1.0 - (x * x) / 2.0) * cos(x) - (x / 2.0) * sin(x);

        double SN = 0.0;
        for (int n = 0; n <= n_max; ++n) {
            // Обчислюємо факторіал 
            double fact = 1.0;
            for (int j = 1; j <= 2 * n; ++j) {
                fact *= j;
            }

            double term = pow(-1, n) * (2.0 * n * n + 1.0) / fact * pow(x, 2 * n);
            SN += term;
            
        }
        double SE = 0.0;
        double res = 0.0;
        int n = 0;
        do{
            double fact = 1.0;
            for (int j = 1; j <= 2 * n; ++j) {
                fact *= j;
            }
            res = pow(-1, n) * (2.0 * n * n + 1.0) / fact * pow(x, 2 * n);
            SE += res;
            n++;
        } while (abs(res) >= e);

         cout << "X= "<< x << " SN= "  << SN << " SN= " <<  SE << " Y= " << Y << endl;
    }
   
    return 0;
}