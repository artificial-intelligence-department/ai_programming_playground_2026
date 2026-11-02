/*
Епік 4. Лабораторна робота № 4 (Варіант 6)
Автор: Туревич Олександр
Група: ШІ-12
*/





#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Функція для друку масиву
void printArray(const int arr[], int size) {

    if (size <= 0) {
        cout << "[порожній масив]" << endl << endl;
        return;
    }
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl << endl;
}

// 3) Знищити елемент із заданим номером
bool removeElementAtPosition(int arr[], int &size, int pos) {
    int index = pos - 1; // перехід від номера до індексу
    if (index < 0 || index >= size) {
        return false;
    }

    // Зсув елементів ліворуч
    for (int i = index; i < size - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    size--;
    return true;
}

// 4) Додати після першого парного елемента масиву елемент зі значенням M[I - 1] + 2
bool insertAfterFirstEven(int arr[], int &size, int maxSize) {
    if (size >= maxSize) {
        return false;
    }

    int evenIndex = -1;
    // Шукаємо перший парний елемент
    for (int i = 0; i < size; ++i) {
        if (arr[i] % 2 == 0) {
            evenIndex = i;
            break;
        }
    }

    if (evenIndex == -1) {
        return false; // парних елементів немає
    }

    // Значення для вставки: значення попереднього (парного) елемента + 2
    int valToInsert = arr[evenIndex] + 2;

    // Зсуваємо елементи праворуч починаючи з кінця
    for (int i = size; i > evenIndex + 1; --i) {
        arr[i] = arr[i - 1];
    }

    arr[evenIndex + 1] = valToInsert;
    size++;
    return true;
}

int main() {
    srand(time(0));
    cout << endl;

    const int MAX_SIZE = 100;
    int arr[MAX_SIZE];
    int size = 10;

    // 1) Сформувати одновимірний масив цілих чисел, використовуючи генератор випадкових чисел
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 50 + 1; // числа від 1 до 50
    }



    // 2) Роздрукувати отриманий масив
    cout <<  "1. Початковий згенерований масив" << endl;
    printArray(arr, size);

    // 3) Знищити елемент із заданим номером (наприклад, номер 3)
    int posToDelete = 0;
    cout << "Введіть номер елемента для видалення (1-" << size << "): ";
    cin >> posToDelete;
    cout << "2. Знищення елемента під номером " << posToDelete << endl;
    if (removeElementAtPosition(arr, size, posToDelete)) {
        cout << "Елемент на позиції " << posToDelete << " успішно видалено." << endl;
    } else {
        cout << "Помилка: невірний номер елемента." << endl;
    }
    cout << "Масив після видалення:" << endl;
    printArray(arr, size);

    // 4) Додати після першого парного елемента елемент зі значенням M[I - 1] + 2
    cout << "3. Додавання після першого парного елемента значення (M[I-1] + 2)" << endl;
    if (insertAfterFirstEven(arr, size, MAX_SIZE)) {
        cout << "Елемент успішно додано!" << endl;
        cout << "Масив після додавання:" << endl;
        printArray(arr, size);
    } else {
        cout << "Парних елементів не знайдено або масив переповнено." << endl;
    }
    

    // 5) Роздрукувати отриманий масив
    cout << "4. Фінальний масив:" << endl;
    printArray(arr, size);

    return 0;
}
