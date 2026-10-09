/*
Алготестер. Задача "Поле чудес"
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    // Введення слова
    string s;
    cin >> s;
    int count = 0; // Лічильник унікальних символів

    // Цикл проходжнння по кожному символу слова
    for (int i = 0; i < s.length(); i++) {
        int repeat = 0;

        // Перевірка, чи зустрічався символ s[i] раніше
        for (int j = 0; j < i; j++) {
            if (s[i] == s[j]) {
                repeat = 1; // Є повтор
                break;
            }
        }

        // Нема повтору
        if (repeat == 0) {
            count++;
        }
    }

    // Виведення остаточного результату
    cout << count << endl;
    return 0;
}