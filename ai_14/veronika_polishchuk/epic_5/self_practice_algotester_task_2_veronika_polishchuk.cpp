//Буквозабирання

#include <iostream>
#include <string>
using namespace std;

// чи дорівнює підрядок s, що починається з позиції p, рядку t
bool ok(string &s, string &t, int p, int d) {
    if (p < 0 || p > d) return false;   // такої позиції не існує
    return s.compare(p, t.size(), t) == 0;
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        string s, t;
        cin >> s >> t;
        int d = s.size() - t.size();    // скільки ходів буде в грі
        bool sergei;

        if (d % 2 == 1) {
            // останній хід робить Ларрі
            // Сірожа виграє, якщо обидві середні позиції підходять
            sergei = ok(s, t, (d - 1) / 2, d) && ok(s, t, (d + 1) / 2, d);
        } else {
            // останній хід робить Сірожа
            // виграє, якщо підходить центр, або обидва сусіди центру
            sergei = ok(s, t, d / 2, d) ||
                     (ok(s, t, d / 2 - 1, d) && ok(s, t, d / 2 + 1, d));
        }

        if (sergei) cout << "Sergei\n";
        else cout << "Larry\n";
    }
    return 0;
}