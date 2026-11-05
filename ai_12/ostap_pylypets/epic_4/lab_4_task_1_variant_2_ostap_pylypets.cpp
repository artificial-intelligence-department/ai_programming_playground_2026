/*лабораторна робота #4 v2*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void printm(int n, int m[]) {
    cout << "Масив елементів: ";
    for (int i = 0; i < n; i++) {
        cout << m[i] << " ";
    }
    cout << endl;
}
void deletefirst(int m[], int& n) {
    for (int i = 0; i < n; i++) {
        if (m[i] == 0) {
            for (int j = i; j < n - 1; j++) {
                m[j] = m[j + 1];
            }
            n--;
            break;
        }
    }
}
void addTwo(int m[], int& n) {
    for (int i = 0; i < n; i++) {
        if (m[i] % 2 == 0) {
            for (int j = n; j > i + 1; j--) {
                m[j] = m[j - 1];
            }

            m[i + 1] = m[i] + 2;
            n++;
            i++;
        }
    }
}
void printres(int m[], int n) {
    cout << "Результат: ";
    for (int i = 0; i < n; i++) {
        cout << m[i] << " ";
    }
    cout << endl;
}
int main() {
    int n, m[200];

    cout << "Введіть кількість елементів масиву: ";
    cin >> n;

    if (cin.fail() || n < 1 || n > 100) {
        cout << "Некоректна кількість елементів.";
        return 1;
    }
    srand(time(0));
    for (int i = 0; i < n; i++) {
        m[i] = rand() % 31;
    }
    printm(n, m);
    deletefirst(m, n);
    addTwo(m, n);
    printres(m, n);
    return 0;
}
