/*
Назва:Красива матриця
Автор: Катерина Лисенко
Група: ШІ-12
*/
#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    int** a = new int*[N];

    for (int i = 0; i < N; i++) {
        a[i] = new int[N];
    }

    // Зчитуємо матрицю
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> a[i][j];
        }
    }

    int changes = 0;
    int expected = 1;

    // Проходимо по діагоналях зліва зверху вправо вниз,
    // починаючи з лівого нижнього кута
    for (int startRow = N - 1; startRow >= 0; startRow--) {
        int i = startRow;
        int j = 0;

        while (i < N && j < N) {
            if (a[i][j] != expected) {
                changes++;
            }

            expected++;
            i++;
            j++;
        }
    }

    // Діагоналі, що починаються у верхньому рядку
    for (int startCol = 1; startCol < N; startCol++) {
        int i = 0;
        int j = startCol;

        while (i < N && j < N) {
            if (a[i][j] != expected) {
                changes++;
            }

            expected++;
            i++;
            j++;
        }
    }

    cout << changes << endl;

    // Звільнення пам'яті
    for (int i = 0; i < N; i++) {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}