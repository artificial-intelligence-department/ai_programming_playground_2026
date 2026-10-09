/*
Алготестер. Задача "Зуби"
*/

#include <iostream>
using namespace std;

int main() {
    // Введення початкових даних
    int n, k;
    cin >> n >> k;

    // Введення масиву гостроти зубів
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int s = 0; // Поточна серія гостроти зубів
    int s_max = 0; // Максимальна серія гостроти зубів

    // Цикл проходження по зубам і їх порівняння з гостротою
    for (int i = 0; i < n; i++) {
        if (a[i] >= k) {
            s++;
            if (s > s_max) {
                s_max = s;
            }
        } else {
            s = 0;
        }
    }

    // Виведення результату
    cout << s_max << endl;
    return 0;
}