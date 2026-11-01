/*
    Задача: Лабораторна робота №4. Варіант №24
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;
int main() {
    int a[100];
    int n; // Довжина кільця
    int k; // Номер елемента, з якого починається виведення кільця
    cout << "Введіть довжину кільця: ";
    cin >> n;
    cout << "Введіть елементи: ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cout << "Введіть номер K: ";
    cin >> k;
    cout << "Початкове кільце: ";
    for (int i = 0; i < n; i++)
    {
        cout << a[(k - 1 + i) % n] << " ";
    }
    cout << endl;
    // Сортування елементів
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j +1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    cout << "Після сортування: ";
    for (int i = 0; i < n; i++)
    {
        cout << a[(k - 1 + i) % n] << " ";
    }
    cout << endl;
    // Видалення парних елементів
    int newN = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] % 2 != 0)
        {
            a[newN] = a[i];
            newN++;
        }
    }
    n = newN;
    cout << "Після видалення парних: ";
    if (n > 0)
    {
        k = (k - 1)% n + 1;
        for (int i = 0; i < n; i++)
        {
            cout << a[(k - 1 + i) % n] << " ";
        }
    }
    cout << endl;
    return 0;
}