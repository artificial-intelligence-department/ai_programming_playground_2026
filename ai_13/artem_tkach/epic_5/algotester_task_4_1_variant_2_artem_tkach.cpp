// Algotester Lab 4, завдання 1, варіант 2 (STL).
// Видалити дублікати, відсортувати числа та циклічно зсунути вліво на K.

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n, k;
    if (!(std::cin >> n >> k)) return 0;

    std::vector<int> values(n);
    for (int &value : values) std::cin >> value;

    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());

    const int size = static_cast<int>(values.size());
    const int shift = k % size;
    std::rotate(values.begin(), values.begin() + shift, values.end());

    std::cout << size << '\n';
    for (int i = 0; i < size; ++i) {
        if (i) std::cout << ' ';
        std::cout << values[i];
    }
    std::cout << '\n';
    return 0;
}
