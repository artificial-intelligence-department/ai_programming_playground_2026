/*
 Lab 2. Task 1. Variant 24.
 Соломія Королюк
 ШІ-13
*/

#include <iostream>
#include <cmath>

using namespace std;

int main(){

    double sum = 0.0;
    short const N = 9;

    for (int n = 1; n <= N; n++){
        double a_n = exp(-sqrt(n));
        sum += a_n;
    }

    cout << "Сума " << N << " членів ряду дорівнює: "  << sum << endl;

    return 0;
}