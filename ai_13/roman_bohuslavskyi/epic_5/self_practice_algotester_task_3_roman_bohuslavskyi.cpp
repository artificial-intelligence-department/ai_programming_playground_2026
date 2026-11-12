/*
Задача:  Примітивна довга арифметика
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    int x, n, k;
    cin >> x >> n >> k;

    string result;
    int count = 0;
    int carry = 0;

    // Рахуємо стовпчики справа наліво, починаючи з одиниць.
    for (int i = 0; i < n + k - 1; i++) {
        // У перших k стовпчиках починаються нові доданки.
        if (i < k) {
            count++;
        }
        // Кожен доданок містить лише n цифр x.
        if (i >= n) {
            count--;
        }

        int sum = x * count + carry;
        int digit = sum % 10;
        carry = sum / 10;
        result += '0' + digit;
    }

    // Дописуємо перенос, який залишився після останнього стовпчика.
    while (carry > 0) {
        result += '0' + carry % 10;
        carry /= 10;
    }

    // Цифри збирали від одиниць, тому виводимо у зворотному порядку.
    int length = result.length();
    for (int i = length - 1; i >= 0; i--) {
        cout << result[i];
    }
    cout << endl;

    return 0;
}
