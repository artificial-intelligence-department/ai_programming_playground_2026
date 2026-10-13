/*Задача: лабораторна робота, завдання 1 (варіант 25)
Хробуст Андрій
Група ШІ-11
*/
#include <iostream>
using namespace std;

int main() {
    long long H, M;
    cin >> H >> M;
    long long h1, m1, h2, m2, h3, m3;
    cin >> h1 >> m1;
    cin >> h2 >> m2;
    cin >> h3 >> m3;
    if ((h1 > 0 && m1 > 0)||(h2 > 0 && m2 > 0) ||(h3 > 0 && m3 > 0)) {
        cout << "NO";//перевірка на затрату тільки одного ресурсу
        return 0;
    }
    H = H - h1 - h2 - h3;//кінцева кількість хп
    M = M - m1 - m2 - m3;//кінцева кількість мани
    if (H > 0 && M > 0) {//перевірка чи залишились мана і хп
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}