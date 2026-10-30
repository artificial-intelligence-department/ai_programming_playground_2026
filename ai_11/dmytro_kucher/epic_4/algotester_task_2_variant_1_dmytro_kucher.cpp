/*
Епік 4. Завдання з Алготестера. Лабораторна робота №2. Варіант №1
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
using namespace std;

int main () {

    int N;
    cin >> N;

    int r[N];
    for (int i = 0; i<N; i++) {
        cin >> r[i];
    }

    if (N < 2) {
        cout << 0;
        return 1;
    }

    int minR = 0;
    bool first = true;

    for (int i = 0; i<N; i++) {

        int min, max;
        bool initialized = false;

        for (int j = 0; j< N; j++) {
            if (j == i) continue;

            if (!initialized) {
                min = r[j];
                max = r[j];
                initialized = true;
            }

            if (r[j]>max) max = r[j];
            if (r[j]<min) min = r[j];
        }

        int d = max - min;

        if (first || d < minR) {
            minR = d;
            first = false;
        }
    }

    cout << minR << "\n";
    
    return 0;
}