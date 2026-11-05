/*
Lab 4 task 1, Нагірний Назарій, ШІ-13, Варіант № 9
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int a[100], n, delet, k;

    cout << "Розмір N: "; cin >> n;
    cout << "Початковий масив: ";
    for (int i = 0; i < n; i++) cout << (a[i] = rand() % 50 + 1) << " ";
    cout << "\n";
 
    cout << "Видалити елемент: "; cin >> delet;
    for (int i = 0; i < n; i++) {
        if (a[i] == delet) {
            for (int j = i; j < n - 1; j++)
            {a[j] = a[j + 1];}
            n--;
            break;
        }
    }

    cout << "Зсув вправо (K): "; cin >> k;
    if (n > 0) {
        k %= n;
        for (int i = 0; i < k; i++) {
            int last = a[n - 1];
            for (int j = n - 1; j > 0; j--) {
                a[j] = a[j - 1];
            }
            a[0] = last;
        }
    }

    cout << "Результат: ";
    for (int i = 0; i < n; i++) 
    {cout << a[i] << " ";}
    return 0;
}