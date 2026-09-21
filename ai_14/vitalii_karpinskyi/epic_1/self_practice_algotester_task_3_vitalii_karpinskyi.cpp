/*
Задачка: Цікава гра (алготестер)
Карпінський Віталій
СШІ-14
*/

#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int cells = n * m; // Загальна кількість клітинок

    if (cells % 2 == 0) { // Якщо кількість  клітинок парна то виграє дракон, інакше виграє Бісеня
        cout << "Dragon" << endl;

    } else {
        cout << "Imp" << endl;
    }

    return 0;
}

