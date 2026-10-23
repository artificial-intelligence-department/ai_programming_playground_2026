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
    //записуємо та начислюємо перемоги
    for (int i = 0; i < n; i++) {
        cin >> c;

        if (c == 'K') {
            kolya++;
        } else if (c == 'V') {
            vasya++;
        }
        //перевірка на виконання необхідних умов на закінчення гри 
        if ((kolya >= 11 || vasya >= 11) &&
            (kolya - vasya >= 2 || vasya - kolya >= 2)) {

            if (kolya > vasya) {
                kolyaWins++;
            } else {
                vasyaWins++;
            }
            //обнулємо результати при виграші одного з учасників
            kolya = 0;
            vasya = 0;
        }
    }

    cout << kolyaWins << ":" << vasyaWins << '\n';
    //виводимо рахунок гри якщо вона не закінчилась
    if (kolya != 0 || vasya != 0) {
        cout << kolya << ":" << vasya << '\n';
    }

    return 0;
}
