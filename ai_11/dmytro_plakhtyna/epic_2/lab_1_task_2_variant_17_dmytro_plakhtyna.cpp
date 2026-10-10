#include <iostream>
using namespace std;
int main () {
    int n, m, rez1;
    bool rez2;
    // Вираз n---m
    cout << "Введіть два числа n i m: ";
    cin >> n >> m;
    rez1 = n --- m;
    cout << "Результат виразу n---m: " << rez1 << endl;
    // Вираз m--<n
    cout << "Введіть два числа m i n: ";
    cin >> m >> n;
    rez2 = m-- < n;
    if (rez2) {
        cout << "Результат виразу m--<n: true" << endl;
    } else {
        cout << "Результат виразу m--<n: false" << endl;
    } 
    return 0;
} 