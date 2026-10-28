 /*
Задача:  Алготестер Lab3v3
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    const int MAX = 100001;
    char text[MAX];

    cin >> text;

    int i = 0;

    while (text[i] != '\0') {
        char letter = text[i];
        int count = 0;

        // Рахуємо, скільки разів буква йде підряд
        while (text[i] == letter) {
            count++;
            i++;
        }

        cout << letter;

        // Для однієї букви кількість не виводимо
        if (count > 1) {
            cout << count;
        }
    }

    cout << endl;

    return 0;
}