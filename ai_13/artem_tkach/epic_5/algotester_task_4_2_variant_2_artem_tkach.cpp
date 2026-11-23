// Algotester Lab 4, завдання 2, варіант 2 (власна реалізація).
// Видалити дублікати, відсортувати числа та циклічно зсунути вліво на K.

#include <iostream>

int main() {
    int n, k;
    if (!(std::cin >> n >> k)) return 0;

    int values[1000];
    for (int i = 0; i < n; ++i) std::cin >> values[i];

    int size = 0;
    for (int i = 0; i < n; ++i) {
        bool alreadyPresent = false;
        for (int j = 0; j < size; ++j) {
            if (values[j] == values[i]) {
                alreadyPresent = true;
                break;
            }
        }
        if (!alreadyPresent) values[size++] = values[i];
    }

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (values[j] < values[i]) {
                int temporary = values[i];
                values[i] = values[j];
                values[j] = temporary;
            }
        }
    }

    const int shift = k % size;
    int rotated[1000];
    for (int i = 0; i < size; ++i) {
        rotated[i] = values[(i + shift) % size];
    }

    std::cout << size << '\n';
    for (int i = 0; i < size; ++i) {
        if (i) std::cout << ' ';
        std::cout << rotated[i];
    }
    std::cout << '\n';
    return 0;
}
