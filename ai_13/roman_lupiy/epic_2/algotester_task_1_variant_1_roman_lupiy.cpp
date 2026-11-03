/*
Задача: lv1
Автор: Роман Лупій
Група: ШІ-13
Варіант: 1
*/
#include <iostream>
using namespace std;

int main() {
    long long H, M;
    cin >> H >> M;

    long long h1, m1;
    long long h2, m2;
    long long h3, m3;

    cin >> h1 >> m1;
    cin >> h2 >> m2;
    cin >> h3 >> m3;

    // Перевіряємо, чи якесь закляття витрачає обидва ресурси.
    if ((h1 > 0 && m1 > 0) ||
        (h2 > 0 && m2 > 0) ||
        (h3 > 0 && m3 > 0)) {
        cout << "NO\n";
        return 0;
    }

    long long usedH = h1 + h2 + h3;
    long long usedM = m1 + m2 + m3;

    if (usedH < H && usedM < M) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}