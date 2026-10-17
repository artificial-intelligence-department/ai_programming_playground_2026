/*
Задача: Лабораторна робота №2, Варіант 19
Автор: Дрогомирецька Ольга
Група: ШІ-13
*/
#include <iostream>
using namespace std;

int main() {
    double n = 2;
    double eps = 0.0001;
    double sum = 0.0;
    double current = n/((n-1)*(n-1));
    while (current >= eps) {
        sum += current;
        current = current *(n+1)*(n-1)*(n-1)/(n*n*n);
        n++;
    }
    cout << "Сума ряду: " << sum << endl;

    return 0;
}