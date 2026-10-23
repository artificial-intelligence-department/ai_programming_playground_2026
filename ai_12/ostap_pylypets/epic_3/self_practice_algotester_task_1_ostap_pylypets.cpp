/*
Self-practice algotestertask 1
тренер слонів
Пилипець Остап ШІ-12
*/
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int a[100001];
    int minPos = 1000000000;
    int maxPos = -1000000000;
    //записуємо значення в масив та знаходимо крайні значення
    for (int i = 0; i < n; i++) {
        cin >> a[i];

        if (a[i] < minPos) {
            minPos = a[i];
        }

        if (a[i] > maxPos) {
            maxPos = a[i];
        }
    }
    //рахуємо кроки
    cout << maxPos - minPos << '\n';

    return 0;
}
