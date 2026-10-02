#include <iostream>

using namespace std;

int main() {
    int x, y;
    
    cout << "Уведіть число x (від 15 до 89): ";
    cin >> x;

    if (x < 15 || x > 89) {
        cout << "Помилка. Число x має бути від 15 до 89." << endl;
        return 1;
    }

    cout << "Уведіть число y (від 15 до 89): ";
    cin >> y;

    if (y < 15 || y > 89) {
        cout << "Помилка. Число y має бути від 15 до 89." << endl;
        return 1;
    }

    cout << "1. Число x = " << x << endl;
    cout << "2. Число y = " << y << endl;

    cout << "3. X у двійковій системі: ";
    int nx = 1;
    while (nx <= x / 2) { // Шукаємо найбільший розряд 2
        nx *= 2;
    }
    int tx = x;
    while (nx > 0) {
        cout << (tx / nx); // Ми виводимо тільки ЦІЛУ частину від ділення, тобто 0 або 1 
        tx %= nx; // Залишок від ділення
        nx /= 2;
    }
    cout << endl;

    cout << "4. Y у двійковій системі: ";
    int ny = 1;
    while (ny <= y / 2) {
        ny *= 2;
    }
    int ty = y;
    while (ny > 0) {
        cout << (ty / ny);
        ty %= ny;
        ny /= 2;
    }
    cout << endl;

    int sum = x + y;
    cout << "5. Сума (" << sum << ") у двійковій системі: ";
    int nsum = 1;
    while (nsum <= sum / 2) { 
        nsum *= 2;
    }
    int tsum = sum;
    while (nsum > 0) {
        cout << (tsum / nsum);
        tsum %= nsum;
        nsum /= 2;
    }
    cout << endl;

    int min;
    if (x < y) {
        min = x;
    } else {
        min = y;
    }

    int result = sum / min;

    cout << "6. Результат ділення (" << result << ") у двійковій системі: ";
    int ndiv = 1;
    while (ndiv <= result / 2) {
        ndiv *= 2;
    }
    int tdiv = result;
    while (ndiv > 0) {
        cout << (tdiv / ndiv);
        tdiv %= ndiv;
        ndiv /= 2;
    }
    cout << endl;

    cout << "7. Результат ділення у десятковій системі: " << result << endl;

    return 0;
}