
/* 
Епік 5. self practice: Algotester, задача "Буквозабирання"
Авторка: Влада Ташогло
Група: ші-11
*/

#include <iostream>
#include <string>
using namespace std;

// Перевірка, чи збігається підрядок s, починаючи з індексу pos, із цільовим рядком t
bool equalAt(string& s, string& t, int pos) {
    for (int i = 0; i < t.size(); ++i) {
        if (s[pos + i] != t[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    int q;
    cin >> q;

    while (q--) {
        string s, t;
        cin >> s >> t;

        // d — загальна кількість кроків, яка буде зроблена обома гравцями
        int d = s.size() - t.size();
        int mid = d / 2;

        bool win;

        // Визначення переможця залежно від того, хто робить останній хід:
        // Якщо d непарне — останній хід робить Ларрі (ходить першим).
        // Ларрі обирає між позиціями mid та mid+1, тому Сірожа виграє лише якщо t стоїть на ОБОХ.
        if (d % 2 == 1) {
            win = equalAt(s, t, mid) && equalAt(s, t, mid + 1);
        }
        // Якщо d парне — останній хід робить Сірожа.
        // Сірожі достатньо мати збіг по центру (mid) або на обох сусідніх позиціях (mid-1 та mid+1).
        else {
            win = equalAt(s, t, mid) || (equalAt(s, t, mid - 1) && equalAt(s, t, mid + 1));
        }

        // Виведення імені переможця
        if (win) {
            cout << "Sergei\n";
        }
        else {
            cout << "Larry\n";
        }
    }

    return 0;
}
