#include <iostream>

using namespace std;

int main() {
    int n;          // кількість днів
    long long h;    // початкова висота дверей
    cin >> n >> h;  // зчитуємо n та h

    int bumps = 0;  // лічильник ударів

    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;   // зріст чергового кота

        if (a > h) {       // якщо кіт вищий за двері
            bumps++;       // додаємо 1 удар
            h++;           // двері розширюються на 1
        }
    }

    cout << bumps << endl; // виводимо результат

    return 0;
}