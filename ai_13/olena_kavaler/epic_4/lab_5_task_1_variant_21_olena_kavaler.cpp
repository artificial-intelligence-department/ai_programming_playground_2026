
/*
Автор: Олена Кавалер
Група: Ші-13
*/

#include <iostream>
using namespace std;

const int ROWS = 100;
const int COLS = 100;

int NumRepeated (int arr[][COLS], int n, int m, bool &found) {

    int best = 0;
    found = false;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int count = 0;

            for (int p = 0; p < n; p++) {
                for (int q = 0; q < m; q++) {
                    if (arr[i][j] == arr[p][q]) {
                        count++;
                    }
                    }
                }
            if (count > 1) {
                        if (!found || arr[i][j] > best) { 
                            found = true;
                            best = arr[i][j];
                    }
                }
            }
        }
    
    return best;
}

int main() {
    
     int n, m;

    do {
        cout << "Введіть кількість рядків (n) та стовпців (m): " << endl;
        cin >> n >> m;
        if (n <= 0 || n > ROWS || m <= 0 || m > COLS) {
        cout << "Помилка: число не підходить" << endl;
        }

    } while(n <= 0 || n > ROWS || m <= 0 || m > COLS); 

    int matrix[ROWS][COLS];
    cout  << "Введіть елементи матриці: " << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }

    bool found;
    int result = NumRepeated(matrix, n, m, found);

    if (found) {
        cout << "Найбільший повторюваний елемент: " << result << endl;
    } else {
        cout << "Повторюваних елементів немає." << endl;
    }

 return 0;
}