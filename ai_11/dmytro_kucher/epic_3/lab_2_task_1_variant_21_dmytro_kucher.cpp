/*
Епік 3. Лабораторна робота №2. Завдання №1. Варіант №21
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
#include<cmath>
using namespace std;

long long factorial (int n) {
    long long result = 1;
    for (int i = 1; i<=n; i++) {
        result *= i;
    }
    return result;
}

int main () {

    long double a[13];
    long double sum = 0;


    for (int i = 1; i<=13; i++) {

        a[i-1] = log(factorial(i)) / pow(i, 2);

        sum += a[i-1];

    }

    cout << "\nРезультат: " << sum << "\n\n";

    return 0;
}