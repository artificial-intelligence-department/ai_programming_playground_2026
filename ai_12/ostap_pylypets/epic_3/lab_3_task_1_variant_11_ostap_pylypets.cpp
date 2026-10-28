/*
Лабораторна робота 3, завдання 1, варіант 11
Пилипець Остап ШІ-12
*/

#include <iostream>
#include <cmath>

int main(){
    int k = 10, n = 10;
    double a = 0.1, b = 1, epselon = 0.0001;
    double h = (b-a)/k;
    //циклом перебираємо всі значення x
    for(int i = 0; i<=k; i++){
        double x = a + i* h;
        double xsquare = x*x;
        double sn = 1;
        double temp = 1;
        //обчислюємо формулу
        for(int q = 1; q<=n; q++){
            temp *= ((2*q+1)*xsquare)/(q * (2.0 * q - 1));
            sn += temp;
        }

        double sumeps = 1;
        int num = 1;
        double temptwo = 1;
        //сума епселон
        while(true){
            temptwo *= ((2*num+1)*xsquare)/(num * (2.0 * num - 1));
            if (std::abs(temptwo) < epselon) {
                break;
            }
            sumeps += temptwo;
            num++;
        }
        // шукаємо для Y
        double y = (1 + 2 * xsquare) * std::exp(xsquare);
        std::cout << "X=" << x
                  << " SN=" << sn
                  << " SE=" << sumeps
                  << " Y=" << y << "\n";
    }

    return 0;
}
