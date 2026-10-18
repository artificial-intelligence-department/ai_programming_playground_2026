/*
lab 3 task 1, Андрій Мадяр, ШІ-13
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main(){
    //ввід змінних
    const double a = 0.1;
    const double b = 0.8;
    int k = 10;
    double step = (b - a)/k;
    double x = a;
    double n_fixed = 10;
    double eps = 0.0001;
    cout << "Обчислення функції" << endl;
    //зовнішній цикл що створює обмеження по значенну х
    for (double x = a; x <= b + 1e-9; x += step) {
        //розрахунок циклу з обмеженням на кількість елементів суми
        double SN = 0.0;
        for (int n = 1; n <= n_fixed; n++) {
            double element = pow(-1, n + 1) * pow(x, 2 * n) / (2 * n * (2 * n - 1));
            SN += element;
        }
        //розрахунок циклом з перевіркою на точність
        double SE = 0.0;
        int n = 1;
        while (true) {
            double element = pow(-1, n + 1) * pow(x, 2 * n) / (2 * n * (2 * n - 1));
            
            //зупинка циклу якщо значення елементу менше за похибку епсилон
            if (fabs(element) < eps) {
                break;
            }
            SE += element;
            n++;
        }
        //розрахунок за формулою функції
        double Y = x * atan(x) - log(sqrt(1.0 + x * x));
        //вивід результатів
        cout << fixed << setprecision(4) << "X=" << setw(6) << x << "   " << setprecision(6) << "SN=" << setw(11) << SN << "   " 
            << "SE=" << setw(11) << SE << "   " << "Y=" << setw(11) << Y << endl;
    }
    return 0;
}