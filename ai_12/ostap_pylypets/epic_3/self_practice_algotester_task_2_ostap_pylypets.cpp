/*
Self-practice algotestertask 2
Коля, Вася і Теніс
Пилипець Остап ШІ-12
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    char c;
    int kolya = 0, vasya = 0;
    int kolyaWins = 0, vasyaWins = 0;

    for (int i = 0; i < n; i++) {
        cin >> c;

        if (c == 'K') {
            kolya++;
        } else if (c == 'V') {
            vasya++;
        }

        if ((kolya >= 11 || vasya >= 11) &&
            (kolya - vasya >= 2 || vasya - kolya >= 2)) {

            if (kolya > vasya) {
                kolyaWins++;
            } else {
                vasyaWins++;
            }

            kolya = 0;
            vasya = 0;
        }
    }

    cout << kolyaWins << ":" << vasyaWins << '\n';

    if (kolya != 0 || vasya != 0) {
        cout << kolya << ":" << vasya << '\n';
    }

    return 0;
}
