/*
 * Задача: Непередбачувана погода (алготестер)
 * Поліщук Вероніка
 * Група 14
 */
#include <iostream>

using namespace std;

int main() {
    int n, a;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        if (a > 0) cout << i << " ";
    }
    
}
