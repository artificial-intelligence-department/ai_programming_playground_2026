/*
Алготестер. Задача "Патріотична стрічка"
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Введення слова
    string s;
    cin >> s;

    int count1 = 0; // Кількість змін для шаблону B, Y, B, Y...
    int count2 = 0; // Кількість змін для шаблону Y, B, Y, B...

    for (int i = 0; i < s.length(); i++) {
        if (i % 2 == 0) {
            // Парні позиції
            if (s[i] != 'B') count1++; // Якщо тут не B, треба міняти для 1-го шаблону
            if (s[i] != 'Y') count2++; // Якщо тут не Y, треба міняти для 2-го шаблону
        } else {
            // Непарні позиції
            if (s[i] != 'Y') count1++; // Якщо тут не Y, треба міняти для 1-го шаблону
            if (s[i] != 'B') count2++; // Якщо тут не B, треба міняти для 2-го шаблону
        }
    }

    // Вивід найменшого з двох чисел
    if (count1 < count2) {
        cout << count1 << endl;
    } else {
        cout << count2 << endl;
    }

    return 0;
}