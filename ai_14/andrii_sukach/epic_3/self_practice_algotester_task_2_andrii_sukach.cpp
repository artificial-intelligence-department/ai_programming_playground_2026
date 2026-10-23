/*Задача: Перехід дороги(Алготестер)
Виконав:Сукач Андрій*/
#include <iostream>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    int a[100005];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int crossings = 0; // Кількість переходів дороги

    for (int i = 1; i < n; i++) {
        if (a[i] % 2 != a[i - 1] % 2) { // Якщо парність поточного будинку не дорівнює парності попереднього
            crossings++; // Перехід дороги
        }
    }

    cout << crossings << "\n";

    return 0;
}