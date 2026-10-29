/*
Епік 4. Лабораторна робота №4. Завдання №1. Варіант №24
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
using namespace std;

int main () {

    const int N_MAX = 100;
    int arr[N_MAX];

    int n;
    cout << "Введіть потужність масиву (від 1 до 100): ";
    cin >> n;

    if (cin.fail() || n<1 || n>N_MAX) {
        cout << "Помилка! Введіть ціле число від 1 до 100\n";
        return 1;
    }

    for (int i = 0; i<n; i++) {
        cout << "Введіть " << i+1 << " елемент масиву: ";
        cin >> arr[i];
        if (cin.fail()) {
            cout << "Помилка! Введіть ціле число\n";
            return 1;
        }
    }

    cout << "\n1) ";

    int qty;
    cout << "Введіть кількість елементів для перегляду: ";
    cin >> qty;

    if (cin.fail() || qty<1) {
        cout << "Помилка! Введіть ціле число, більше за 0\n";
        return 1;
    }

    int a = 0;
    for (int i = 0; i<qty; i++) {
        cout << arr[a] << " ";
        a = (a+1) % n;
    }

    cout << "\n\n2) ";
    
    int k;
    cout << "Введіть порядковий номер елемента, починаючи з якого масив буде виводитись: ";
    cin >> k;

    if (cin.fail() || k<1 || k>n) {
        cout << "Помилка! Введіть натуральне число, не більше за кількість елементів масиву\n";
        return 1;
    }

    for (int i = 0; i<n; i++) {
        int index = (k - 1 + i) % n;
        cout << arr[index] << " ";
    }

    cout << "\n\n3) ";

    for (int i = 0; i<n-1; i++) {
        for (int j = 0; j<n-1-i; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    for (int i = 0; i<n; i++) {
        cout << arr[i] << " ";
    } 

    cout << "\n\n4) ";

    for (int i = 0; i<n; i++) {
        if (arr[i] % 2 == 0) {
            for (int j = i; j<n-1; j++) {
                arr[j] = arr[j+1];
            }
            n--;
            i--;
        }
    }

    if (n == 0) {
        cout << "Кільце порожнє! Усі елементи видалено\n\n";
        return 0;
    }

    for (int i = 0; i<n; i++) {
        cout << arr[i] << " ";
    }

    cout << "\n\n5) ";

    cout << "Введіть порядковий номер елемента, починаючи з якого масив буде виводитись: ";
    cin >> k;

    if (cin.fail() || k<1 || k>n) {
        cout << "Помилка! Введіть натуральне число, не більше за кількість елементів масиву\n";
        return 1;
    }

    for (int i = 0; i<n; i++) {
        int index = (k - 1 + i) % n;
        cout << arr[index] << " ";
    }

    return 0;
}