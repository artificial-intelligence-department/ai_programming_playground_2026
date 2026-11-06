/*
Задача: Алготестер. Лабораторна 3, варіант 3
Автор: Ольга Дрогомирецька
Група: ШІ-13
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;

    int n = s.length(); 
    int count = 1;

    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) {
            // Поточна буква продовжує групу однакових букв.
            count++;
        } else {
            // Група закінчилася: виводимо її букву.
            cout << s[i - 1];

            // Кількість виводимо тільки для повторень.
            if (count > 1) {
                cout << count;
            }
            // Поточна буква починає нову групу.
            count = 1;
        }
    }
    // Останню групу виводимо окремо, бо після неї немає іншої букви.
    cout << s[n - 1];

    if (count > 1) {
        cout << count;
    }

    cout << '\n';
    return 0;
}