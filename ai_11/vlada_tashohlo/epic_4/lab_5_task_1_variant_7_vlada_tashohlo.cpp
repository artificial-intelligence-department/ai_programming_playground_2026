
/* 
Епік 4. Лабораторна робота 5. Варіант 7.
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

// Функція для введення одного цілого числа з перевіркою коректності
int inputInt(string message) {
    string line;
    int x;
    char extra;

    while (true) {
        cout << message;
        getline(cin, line);

        stringstream ss(line);

        if (ss >> x && !(ss >> extra)) {
            return x;
        }

        cout << "Помилка! Потрібно ввести одне ціле число.\n";
    }
}

// Функція для обміну рядка та стовпця квадратної матриці
void change(int** a, int n, int row, int col) {
    for (int k = 0; k < n; ++k) {
        int temp = a[row][k];
        a[row][k] = a[k][col];
        a[k][col] = temp;
    }
}

// Функція для виведення матриці на екран
void printArray(int** a, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    int n, m;

    // Введення кількості рядків з перевіркою
    do {
        n = inputInt("Кількість рядків: ");
        if (n <= 0) {
            cout << "Кількість рядків має бути додатною.\n";
        }
    } while (n <= 0);

    // Введення кількості стовпців з перевіркою
    do {
        m = inputInt("Кількість стовпців: ");
        if (m <= 0) {
            cout << "Кількість стовпців має бути додатною.\n";
        }
    } while (m <= 0);

    // Виділення пам'яті під матрицю
    int** a = new int*[n];

    for (int i = 0; i < n; ++i) {
        a[i] = new int[m];
    }

    int mode;

    // Вибір режиму заповнення матриці
    do {
        mode = inputInt("Оберіть спосіб заповнення (1 - вручну, 2 - рандом): ");

        if (mode != 1 && mode != 2) {
            cout << "Оберіть 1 або 2.\n";
        }
    } while (mode != 1 && mode != 2);

    if (mode == 1) {
        // Самостійне введення матриці
        cout << "Вводьте елементи окремо для кожного рядка.\n";

        // Введення кожного рядка з перевіркою кількості та типу елементів
        for (int i = 0; i < n; ++i) {
            while (true) {
                cout << "Рядок " << i + 1 << " (потрібно " << m << " цілих чисел): ";

                string line;
                getline(cin, line);
                stringstream ss(line);

                int count = 0;
                bool valid = true;

                while (count < m) {
                    if (!(ss >> a[i][count])) {
                        valid = false;
                        break;
                    }
                    ++count;
                }

                char extra;
                if (valid && (ss >> extra)) {
                    valid = false;
                }

                if (valid && count == m) {
                    break;
                }

                cout << "Помилка! Введіть рівно " << m << " цілих чисел у цьому рядку.\n";
            }
        }
    } else {
        // Заповнення випадковими числами
        int minValue, maxValue;

        // Введення діапазону для випадкових чисел
        minValue = inputInt("Мінімум діапазону: ");
        maxValue = inputInt("Максимум діапазону: ");

        while (minValue > maxValue) {
            cout << "Мінімум не може перевищувати максимум.\n";
            minValue = inputInt("Мінімум діапазону: ");
            maxValue = inputInt("Максимум діапазону: ");
        }

        srand(time(0));

        // Заповнення матриці випадковими числами з заданого діапазону
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = minValue + rand() % (maxValue - minValue + 1);
            }
        }
    }

    // Виведення початкової матриці
    cout << "Початкова матриця:\n";
    printArray(a, n, m);

    // Перевірка, чи квадратна матриця для можливості обміну
    if (n != m) {
        cout << "Виконати повний обмін рядків і стовпців неможливо, оскільки їхня кількість елементів різна.\n";
    } else {
        // Зберігаємо перший рядок і перший стовпець для пошуку пар елементів
        int* firstRow = new int[n];
        int* firstCol = new int[n];

        for (int i = 0; i < n; ++i) {
            firstRow[i] = a[0][i]; // перший рядок
            firstCol[i] = a[i][0]; // перший стовпець
        }

        // Масиви для збереження індексів пар (рядок, стовпець), які потрібно обміняти
        int* rows = new int[n * n];
        int* cols = new int[n * n];
        int count = 0;

        // Пошук пар елементів, які співпадають у першому рядку та першому стовпці
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (firstCol[i] == firstRow[j]) {
                    rows[count] = i;
                    cols[count] = j;
                    ++count;
                }
            }
        }

        // Виконання обмінів для знайдених пар
        for (int i = 0; i < count; ++i) {
            change(a, n, rows[i], cols[i]);
        }

        // Виведення матриці після обмінів
        cout << "Матриця після обмінів:\n";
        printArray(a, n, m);

        // Звільнення пам'яті для допоміжних масивів
        delete[] firstRow;
        delete[] firstCol;
        delete[] rows;
        delete[] cols;
    }

    // Звільнення пам'яті для матриці
    for (int i = 0; i < n; ++i) {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}