/*Epic 4 - Завдання 1 лабораторної 4 варіант 3
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <cstdlib> 
#include <ctime>   

using namespace std;

int main() {
    srand(time(0)); // Ініціалізація генератора рандому

    int N = 10;

    // Створюємо масив із запасом для одного нового елемента
    int M[N + 1];

    // 1) Заповнення випадковими числами від 0 до 9
    for (int i = 0; i < N; i++) {
        M[i] = rand() % 10; 
    }

    // 2) Друк початкового масиву
    cout << "Початковий масив: ";
    for (int i = 0; i < N; i++) {
        cout << M[i] << " ";
    }
    cout << "\n";

    // 3) Видалення всіх нулів
    int new_size = 0;
    for (int i = 0; i < N; i++) {
        if (M[i] != 0) {
            M[new_size] = M[i];
            new_size++;
        }
    }
    N = new_size; // Оновлюємо розмір масиву

    // 4) Пошук першого парного елемента
    int first_even = -1;
    for (int i = 0; i < N; i++) {
        if (M[i] % 2 == 0) {
            first_even = i;
            break; 
        }
    }

    // Вставка нового елемента, якщо парний знайдено
    if (first_even != -1) {
        // Зсув елементів вправо для звільнення місця
        for (int i = N; i > first_even + 1; i--) {
            M[i] = M[i - 1];
        }

        M[first_even + 1] = M[first_even] + 2;
        N++;
    }

    // 5) Друк кінцевого масиву
    cout << "Кінцевий масив:   ";
    for (int i = 0; i < N; i++) {
        cout << M[i] << " ";
    }
    cout << "\n";

    return 0;
}