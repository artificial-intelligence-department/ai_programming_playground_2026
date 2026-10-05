/*
 Lab 1. Task 2. Variant 12.
 Соломія Королюк
 ШІ-13
*/

#include <iostream>
#include <cmath>

using namespace std;

int main(){

    int n, m;

    cout << "Введіть значення n: ";
    cin >> n;
    cout << "Введіть значення m: ";
    cin >> m;

    int res1 = n++ * m;
    cout << "Результат виразу n++ * m: " << res1 << endl;
    cout << "n:" << " " << n << " m:"<< " " << m << endl;

    int res2 = n++ < m;
    cout << "Результат виразу n++ < m: " << res2 << endl;
    cout << "n:" << " " << n<< " m:"<< " " << m << endl;

    int res3 = n-- > m++;
    cout << "Результат виразу n-- > m++: " << res3 << endl;
    cout << "n:" << " " << n << " m:"<< " " << m << endl;
    
    return 0;
}