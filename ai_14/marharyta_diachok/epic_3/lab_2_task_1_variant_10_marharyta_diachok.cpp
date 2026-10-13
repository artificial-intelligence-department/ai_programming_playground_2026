/* 
Задача: Лабораторна робота №2. Завдання 1. Варіант №10. 
Автор: Дячок Маргарита.
Група: ШІ-14
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n = 1;
    double a = n/(2.0 * n);
    double sum = a;
    while (a >= 0.0001) {
        a = a * (1.0/(2.0 * (2 * n + 1)));
        sum += a;
        n++;
        
    }
cout << sum << endl;

    return 0;
}