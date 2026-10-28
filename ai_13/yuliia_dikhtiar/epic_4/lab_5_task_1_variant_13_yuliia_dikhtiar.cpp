/*
Назва задачі: Lab 5 Task 1
Варіант: 13
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>

using namespace std;

const int rMax = 100;
const int cMax = 100;

int findCol(int a[][cMax], int n, int m) {

    // Шукаємо стовпець, для якого сума зліва більша за суму справа
    for (int col = 1; col < m - 1; col++) {

        long long sumLeft = 0;
        long long sumRight = 0;

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < col; j++) {
                sumLeft += a[i][j];
            }

            for (int j = col + 1; j < m; j++) {
                sumRight += a[i][j];
            }
        }

        if (sumLeft > sumRight) {
            return col;
        }
    }

    return -1;
}

int main () {

    int a[rMax][cMax];
    int n = 0;
    int m = 0;

    cout << "Висота: ";
    inputHeight:
    cin >> n;

    if(cin.fail() || n <= 0 || n > 100) {
        cout << "Введіть ціле число від 1 до 100";
        cin.clear();
        cin.ignore(10000, '\n');
        goto inputHeight;
    }

    cout << "Ширина: ";
    inputWidth:
    cin >> m;

    if(cin.fail() || m <= 0 || m > 100) {
        cout << "Введіть ціле число від 1 до 100";
        cin.clear();
        cin.ignore(10000, '\n');
        goto inputWidth;
    }

    cout << "Введіть елементи масиву: " << endl;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            numberInput:
            cin >> a[i][j];
            if(cin.fail()) {
                cout << "Введіть ціле число";
                cin.clear();
                cin.ignore(10000, '\n');
                goto numberInput;
            }
        }
    }
    cout << endl;

    cout << "Початковий масив:" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Знаходимо потрібний стовпець
    int col = findCol(a, n, m);

    if (col == -1) {
        cout << "Такого стовпця не існує.\n";
    }
    else {
        cout << "Знайдено стовпець номер " << col + 1 << endl;
    }

    return 0;
}