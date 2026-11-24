/*
Назва: Сапер
Автор: Макух Арсеній
Група: ШІ-13
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    string field = "";
    string answ_field = "";
    int el_value = 0;
    int field_length;

    cin >> field_length;

    cin >> field;

    if (field.length() != field_length) {
        cout << "Довжина рядка не збігається." << endl;
        return 1;
    }

    for (int i = 0; i < field_length; i++) {
        if (field[i] != '.' && field[i] != '*') {
            cout << "Поле може складатись лише з . та *" << endl;
            return 1;
        }
    }

    answ_field = field;

    for (int i = 0; i < field_length; i++) {
        el_value = 0;

        if (field[i] == '.') {
            if (i > 0 && field[i - 1] == '*') {
                el_value++;
            }

            if (i < field_length - 1 && field[i + 1] == '*') {
                el_value++;
            }

            answ_field[i] = '0' + el_value;
        }
    }

    cout << answ_field << endl;

    return 0;
}
