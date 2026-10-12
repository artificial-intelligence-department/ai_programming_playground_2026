#include <iostream>
#include <algorithm>
using namespace std;

bool visokos(int year) { // Функція для перевірки, чи є рік високосним
    return year % 400 == 0 ||
           (year % 4 == 0 && year % 100 != 0); // 
}

int main() {
    long long n;
    cin >> n;

    long long cycle = n / 400; // кількість повних циклів по 400 років
    int ostacha = n % 400; // кількість неповних років

    long long base = cycle * 97; // 97 високосних років у кожному циклі по 400 років

    int minimum = ostacha; // треба задати таке число щоб потім в minimum = min(minimum, count); вибралось count
    int maximum = 0;

    for (int start = 1; start <= 400; start++) { // старт - рік, з якого починається неповний цикл
        int count = 0;

        for (int i = 0; i < ostacha; i++) {
            int year = (start + i - 1) % 400 + 1; // обчислюємо рік у циклі від 1 до 400

            if (visokos(year)) {
                count++;
            }
        }

        minimum = min(minimum, count);
        maximum = max(maximum, count);
    }

    cout << base + minimum << " " << base + maximum;
    return 0;
}