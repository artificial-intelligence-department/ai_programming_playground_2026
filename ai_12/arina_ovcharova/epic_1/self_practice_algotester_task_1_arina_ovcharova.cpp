#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;  // Послідовність команд
    int x, y;  // Координати цільової точки
    cin >> s >> x >> y;

    int r = 0; // Лічильник команд 'R' (рух вправо)
    int u = 0; // Лічильник команд 'U' (рух вгору)

    // Рахуємо, скільки у нас є команд кожного типу
    for (char c : s) {
        if (c == 'R') r++;
        if (c == 'U') u++;
    }

    // Для точки (x, y) потрібно хоча б x команд 'R' та y команд 'U'
    if (r >= x && u >= y) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}