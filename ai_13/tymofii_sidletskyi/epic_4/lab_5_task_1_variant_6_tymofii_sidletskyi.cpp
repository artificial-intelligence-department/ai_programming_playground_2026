#include <iostream>
using namespace::std;
/* Лаб 5 варіант 6
   Сідлецький Тимофій ШІ-13
*/

void points (int rowsf, int colsf, int mf[][10]) {
    bool found = false;
    for (int i = 0; i < rowsf; i++) {
        for (int j = 0; j < colsf; j++) {
            int current = mf[i][j];
            bool max_in_row = true;
            bool min_in_col = true;

            for (int k = 0; k < rowsf; k++) {
                if (mf[i][k] > current) {
                    max_in_row = false;
                    break;
                }
            }
            for (int k = 0; k < colsf; k++) {
                if (mf[k][j] < current) {
                    min_in_col = false;
                    break;
                }
            }

            bool max_in_col = true;
            bool min_in_row = true;

            for (int k = 0; k < rowsf; k++) {
                if (mf[k][j] > current) {
                    max_in_col = false;
                    break;
                }
            }
            for (int k = 0; k < colsf; k++) {
                if (mf[i][k] < current) {
                    min_in_row = false;
                    break;
                }
            }

            if ((max_in_row && min_in_col) || (max_in_col && min_in_row)) {
                cout << "Сідлова точка: " << current << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "Сідлових точок не знайдено" << endl;
    }
    return;
}

int main () {
    const int max_rows = 10;
    const int max_cols = 10;
    int m[max_rows][max_cols];
    int rows;
    int cols;

    cout << "К-сть рядків (1-10): ";
    cin >> rows;
    if (rows < 0 || rows > max_rows || cin.fail()) {
        cout << "Некоректна к-сть рядків";
        return 1;
    }

    cout << "К-сть стовпців(1-10): ";
    cin >> cols;
    if (cols < 0 || cols > max_cols || cin.fail()) {
        cout << "Некоректна к-сть стовпців";
        return 1;
    }
    cout << "Елементи матриці: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> m[i][j];
        }
    }

    points(rows, cols, m);
    return 0;
}