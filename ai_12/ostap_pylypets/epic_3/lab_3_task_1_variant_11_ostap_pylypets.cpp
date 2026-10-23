/*
Лабораторна робота 3, завдання 1, варіант 11
Пилипець Остап ШІ-12
*/
#include <iostream>
#include <cmath>

int main(){
    //вводиом змінні
    int k = 10, n = 10;
    double a = 0.1, b = 1, epselon = 0.0001;
    double h = (b-a)/k;
    //цикл for який перебирає всі значення на проміжку
    for(int i = 0; i<=k; i++){
        //обчислення формул
        double x = a + i* h;
        double xsquare = x*x;
        double sn = 1;
        double temp = 1;
        //цикл for j обчислює суму 10 членів ряду
        for(int q = 1; q<=n; q++){
            temp *= ((2*q+1)*xsquare)/(q * (2.0 * q - 1));
            sn += temp;
        }
        double sumeps = 1;
        int num = 1;
        double temptwo =1;
        //цикл який буде виконуватися доки похибка не буде менша за епселон
        while(true){
            temptwo *=((2*num+1)*xsquare)/(num * (2.0 * num - 1));
            if (abs(temptwo) < epselon) {
                break;
            }
            sumeps += temptwo;
            num++;
        }
        std::cout << sn << " " << sumeps << "\n";
    }
    return 0;
}