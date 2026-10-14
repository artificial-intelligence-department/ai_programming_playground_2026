/*
    Задача: Максимум
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int maxV = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > maxV) {
            maxV = a[i];
        }
    }

    cout << maxV;
}