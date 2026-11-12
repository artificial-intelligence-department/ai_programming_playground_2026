#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <cmath>

using namespace std;

const int MAX_SIZE = 100;

//ф-я виведення масиву
void printArray(const int* array, int size) { 
    if (size == 0) {
        cout << "Масив порожній." << endl;
        return;
    }
    for (int i = 0; i < size; ++i) {
        cout << *(array + i) << " "; // Використання вказівників / *(a + i) == a[i]
    }
    cout << endl;
}

int main() {
    // Ініціалізація генератора випадкових чисел
    srand(static_cast<unsigned int>(time(0)));

    int M[MAX_SIZE];
    int n;

    // Введення розміру та формування масиву
    cout << "Введiть реальний розмiр масиву (не бiльше " << MAX_SIZE << "): ";
    cin >> n;

    if (n <= 0 || n > MAX_SIZE) {
        cout << "Некоректний розмiр масиву!" << endl;
        return 1;
    }

    // Заповнення випадковими числами в діапазоні від -100 до 100
    for (int i = 0; i < n; ++i) {
        *(M + i) = rand() % 201 - 100; 
    }

    cout << endl << "Початковий масив:" << endl;
    printArray(M, n);

    // Знищення елементів, кратних 3
    int new_n = 0;
    for (int i = 0; i < n; ++i) {
        if (i % 3 != 0) {
            *(M + new_n) = *(M + i);
            new_n++;
        }
    }
    n = new_n; // Оновлена довжина масиву

    cout << endl << "Масив пiсля вилучення елементiв з індексами, кратними 3:" << endl;
    printArray(M, n);

    // Додавання після кожного від’ємного елемента елемент зі значенням |M[i-1] + 1|, M[i-1] - попередній елемент
    for (int i = 0; i < n; ++i) {
        if (*(M + i) < 0) {
            if (n >= MAX_SIZE) {
                cout << endl << "Досягнуто максимальний розмiр масиву!" << endl;
                break;
            }

            int prev_value;
                if (i > 0) {
                prev_value = *(M + i - 1); // Якщо індекс більший за 0, беремо попередній елемент
                } else {
                prev_value = 0;            // Якщо ми на самому початку масиву (індекс 0), беремо 0
                }
            int new_val = abs(prev_value + 1);

            // Зсув елементів вправо, щоб звільнити місце 
            for (int j = n; j > i + 1; --j) {
                *(M + j) = *(M + j - 1);
            }

            *(M + i + 1) = new_val; // Вставка елемента
            n++;
            i++; // Пропуск новового елемента, щоб не обробляти його в циклі
        }
    }

    cout << endl << "Пiдсумковий масив (пiсля додавання нових елементiв):" << endl;
    printArray(M, n);

    return 0;
}