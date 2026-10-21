/*
    Алготестер. "Коля, Вася і Теніс"
    Гончаренко Семен
    ШІ-11
*/

#include <iostream>

using namespace std;

int main() {
    int n = 0;
    char goal = '0';
    int k = 0;
    int v = 0;
    int win_k = 0;
    int win_v = 0;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> goal;
        if (goal == 'K') {
            k += 1;
        }
        if (goal == 'V') {
            v += 1;
        }
        if (k >= 11 or v >= 11) {
            if (k-v >= 2) {
                win_k += 1;
                k = 0;
                v = 0;
            }
            if (v-k >= 2) {
                win_v += 1;
                k = 0;
                v = 0;
            }
        }
    }
    cout << win_k << ":" << win_v << endl;
    if (k != 0 or v != 0) {
        cout << k << ":" << v << endl;
    }
    return 0;
}