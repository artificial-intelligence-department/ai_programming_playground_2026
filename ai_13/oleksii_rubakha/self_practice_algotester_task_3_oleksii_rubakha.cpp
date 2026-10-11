/*
Патріотична стрічка, Олексій Рубаха, ШІ-13
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;

    string first = "";
    string second = "";

    // Створюємо дві можливі патріотичні стрічки: одна починається з блакитного, інша з жовтого
    for (int i = 0; i < s.length(); i++) {
        // Перша патріотична стрічка: чергуємо блакитний і жовтий
        if (i % 2 == 0) {
            first += 'B';
            second += 'Y';
            // Друга патріотична стрічка: чергуємо жовтий і блакитний
        } else {
            first += 'Y';
            second += 'B';
        }
    }

    int countFirst = 0;
    int countSecond = 0;

    // Порівнюємо вхідну стрічку з обома патріотичними варіантами та рахуємо кількість необхідних змін
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != first[i]) {
            countFirst++;
        }
        if (s[i] != second[i]) {
            countSecond++;
        }
    }

    // Виводимо мінімальну кількість змін, необхідних для перетворення стрічки на патріотичну
    if (countFirst < countSecond) {
        cout << countFirst;
    } else {
        cout << countSecond;
    }

    return 0;
}
