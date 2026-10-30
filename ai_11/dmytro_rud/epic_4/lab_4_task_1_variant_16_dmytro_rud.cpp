#include <iostream>
#include <limits>

using namespace std;

const int MAX_SIZE = 100;

int menu() {
    int choose;

    while (true) {
        cout << "\n1 - додати новий елемент у чергу\n";
        cout << "2 - видалити елемент із черги\n";
        cout << "3 - переглянути поточний вміст черги\n";
        cout << "0 - завершити роботу програми\n";
        cout << "Виберіть операцію: ";

        if (!(cin >> choose)) {
            cout << "Помилка! Введіть число від 0 до 3.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choose >= 0 && choose <= 3) {
            return choose;
        }

        cout << "Такого коду не існує. Введіть коректне значення.\n";
    }
}

void printQueue(const int arr[], int size) {
    if (size == 0) {
        cout << "Черга порожня.\n";
        return;
    }

    cout << "Черга: ";

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    cout << "\n";
}

void add(int arr[], int& size) {
    if (size == MAX_SIZE) {
        cout << "Черга заповнена. Додати елемент неможливо.\n";
        return;
    }

    int value;

    cout << "Введіть значення, яке потрібно додати: ";

    while (!(cin >> value)) {
        cout << "Помилка! Введіть ціле число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    arr[size] = value;
    size++;

    cout << "Елемент додано.\n";
}

void removeFirst(int arr[], int& size) {
    if (size == 0) {
        cout << "Черга порожня. Видаляти нічого.\n";
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    size--;

    cout << "Перший елемент черги видалено.\n";
}

int main() {
    int arr[MAX_SIZE];
    int size = 0;
    int choose;

    do {
        choose = menu();

        switch (choose) {
            case 1:
                add(arr, size);
                printQueue(arr, size);
                break;

            case 2:
                removeFirst(arr, size);
                printQueue(arr, size);
                break;

            case 3:
                printQueue(arr, size);
                break;

            case 0:
                cout << "Роботу програми завершено.\n";
                break;
        }

    } while (choose != 0);

    return 0;
}
