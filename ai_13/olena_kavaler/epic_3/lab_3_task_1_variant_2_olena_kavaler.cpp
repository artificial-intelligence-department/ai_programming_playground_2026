
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {

    double a = M_PI / 5.0; // початок діапазону      
    double b = 9.0 * M_PI / 5.0; // кінець діапазону
    int k = 10;                  
    int n_fixed = 40;            
    double eps = 0.0001;

    // крок зміни x
    double step = (b - a) / k;

     cout << "Обчислення функції" << endl;

    for (double x = a; x <= b; x += step) {
        
        double SN = 0.0;
        for (int i = 1; i <= n_fixed; i++) {
            double term = cos(i * x) / i; // формуємо поточний член ряду
            SN += term;
        }

        double SE = 0.0;
        double term_e;
        int i = 1;

        do {
            term_e = cos(i * x) / i;
            SE += term_e;
            i++;
        } while (fabs(term_e) >= eps);

        // точне значення
        double Y = -log(fabs(2 * sin(x / 2.0)));

        cout << "X = " << x 
             << " \tSN = " << SN 
             << " \tSE = " << SE 
             << " \tY = " << Y << endl;
    }

    return 0;


}
