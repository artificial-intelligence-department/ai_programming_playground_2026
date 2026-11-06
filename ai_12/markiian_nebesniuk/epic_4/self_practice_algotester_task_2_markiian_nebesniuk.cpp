/*
Задача Алготестер "Лотерея"
Небеснюк Маркіян
ШІ-12
*/

#include <iostream>
using namespace std;

int a[1005][1005]; 

int main() {
    int n, m;
    cin >> n >> m;

    // Зчитування матриці розміром n x m
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    // Масив для збереження максимумів кожного стовпчика
    int max[m];
    for (int i = 0; i < m; i++) {
        max[i] = 0;
    }

    // Пошук максимального елемента у кожному стовпчику
    int max_num = 0;
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (a[i][j] > max_num) max_num = a[i][j];
        }
        max[j] = max_num;
        max_num = 0;
    }

    int result = max[0]; // Беремо перший елемент за початковий мінімум

    // Пошук мінімального значення серед усіх максимумів стовпчиків
    for (int i = 0; i < m; i++) {
        if (max[i] < result) {
            result = max[i];
        }
    }

    cout << result << endl;

    return 0;
}