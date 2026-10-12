/*
Хелловін, Артем Момоток, ШІ-13
*/
#include <iostream>
using namespace std;

int main() {

    // Кількість цукерок в мішках Зеника та Марічки
    int n, m;

    // Зчитуємо їх кількість відповідно
    cin >> n >> m;

    // Масиви для зберігання цін
    double price1[100];
    double price2[100];

    // Заповнюємо перший масив вартостями цукерок Зеника
    for (int i = 0; i < n; i++) {
        cin >> price1[i];
    }

    // Заповнюємо другий масив вартостями цукерок Марічки
    for (int i = 0; i < m; i++) {
        cin >> price2[i];
    }

    // Знаходимо мінімальну вартість цукерки в мішку Зеника
    double min1 = price1[0];
    for (int i = 1; i < n; i++) {
        if (price1[i] < min1) min1 = price1[i];
    }

    // Знаходимо мінімальну вартість цукерки в мішку Марічки
    double min2 = price2[0];
    for (int i = 1; i < m; i++) {
        if (price2[i] < min2) min2 = price2[i];
    }

    // Виводимо суму мінімальних вартостей цукерок з обох мішків
    cout << endl;
    cout << min1 + min2 << endl;

    return 0;

}