#include <algorithm>
#include <iostream>
using namespace std;

const int N = 100;

    // Функція перевіряє, чи впорядкований рядок n по зростанню або спаданню
    int check(int m[N][N], int n, int b) {
        bool result_asc = true;  // Припущення: рядок відсортовано по зростанню
        bool result_desc = true; // Припущення: рядок відсортовано по спаданню

        // Перевірка на зростання
        for (int i = 1; i < b; i++) {
            if (m[n][i] < m[n][i - 1]) {
                result_asc = false; // Якщо наступний менший за попередній, то не зростає
            }
        }

        // Перевірка на спадання
        for (int i = 1; i < b; i++) {
            if (m[n][i] > m[n][i - 1]) {
                result_desc = false; // Якщо наступний більший за попередній, то не спадає
            }
        }

        if (result_desc == true) return 1; // Спадає
        else if (result_asc == true) return 2; // Зростає
        else if (result_asc == true && result_desc == true) return -1; // Усі елементи однакові
        else return 0; // Не впорядковано (ні зростає, ні спадає)
    }

    // Функція впорядковує по зростанню всі рядки, які не впорядковані по спаданню
    void sort(int m[N][N], int a, int b) {
        for (int i = 0; i < a; i++) {
            if (check(m, i, b) == 2 || check(m, i, b) == -1 || check(m, i, b) == 0) {
                sort(m[i], m[i] + b);
            }
        }
    }

    int main() { 
        int M[N][N];

        int a; // Кількість рядків
        cin >> a;

        int b; // Кількість стовпців
        cin >> b;

        // Заповнення матриці
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                cin >> M[i][j];
            }
        }
        
        int n;
        cin >> n;
        
        if (check (M, n - 1, b) == 1) cout << "Спадає" << endl;
        else if (check (M, n - 1, b) == 2) cout << "Зростає" << endl;
        else cout << "Не зростає і не спадає" << endl;

        // Впорядковуємо потрібні рядки по зростанню
        sort(M, a, b);

        // Виводимо кінцеву матрицю
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                cout << M[i][j] << " ";
            }
            cout << endl;
        }

        return 0;
    }