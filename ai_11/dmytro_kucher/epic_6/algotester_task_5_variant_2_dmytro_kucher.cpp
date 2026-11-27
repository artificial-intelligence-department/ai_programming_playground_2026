/*
Епік 6. Завдання з Алготестера. Лабораторна робота №5. Завдання №1. Варіант №2
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <iostream>
using namespace std;

int main () {

    int N, M;
    cin >> N >> M;

    if (N<1 || N>1000 || M<1 || M>1000) return 1;

    char cave[1000][1001];

    for (int i = 0; i<N; i++) {
        cin >> cave[i];
    }

    for (int j = 0; j<M; j++) {
        int bottom = N-1;
        for (int i = N-1; i>=0; i--) {
            if (cave[i][j] == 'X') bottom = i-1;
            else if (cave[i][j] == 'S') {
                cave[i][j] = 'O';
                cave[bottom][j] = 'S';
                bottom--;
            }
        }        
    }

    cout << "\n";

    for (int i = 0; i<N; i++) {
        for (int j = 0; j<M; j++) {
            cout << cave[i][j];
            if (j==M-1) cout << "\n";
        }
    }

    return 0;
}