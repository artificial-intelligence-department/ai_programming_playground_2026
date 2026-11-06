/*
Епік 4. Завдання з Алготестера. Лабораторна робота №2. Варіант №1
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
#include <climits>
using namespace std;

int main () {

    int N;
    cin >> N;

    int* r = new int[N];
    for (int i = 0; i<N; i++) {
        cin >> r[i];
    }

    if (N <= 2) {
        cout << 0;
        delete[] r;
        return 0;
    }

    int max1 = INT_MIN;
    int max2 = INT_MIN;

    int min1 = INT_MAX;
    int min2 = INT_MAX;

    for (int i = 0; i<N; i++) {

        if (r[i] >= max1) {
            max2 = max1;
            max1 = r[i];
        }
        else if (r[i] > max2) {
            max2 = r[i];
        }

        if (r[i] <= min1) {
            min2 = min1;
            min1 = r[i];
        }
        else if (r[i] < min2) {
            min2 = r[i];
        }
    }

    int m = max1 - min2;
    if (max2 - min1 < m) m = max2 - min1;

    cout << m << "\n";

    delete[] r;
    
    return 0;
}