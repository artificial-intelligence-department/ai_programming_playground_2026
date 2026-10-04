/*
Задача: Допоможе чи заб'є?
Карпінський Віталій
СШІ-14
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
    // Введення даних
    int k;
    string s;
    cin >> k;
    cin >> s;

    long count = 0;
    long pos = 0;
    // Пошук рядка "TOILET"
    while (pos = s.find("TOILET", pos)) {
        if (pos == -1) {
            break;
        }
        count++;
        pos += 6;
    }
    // Допоможе чи ні
    if (count >= k) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}