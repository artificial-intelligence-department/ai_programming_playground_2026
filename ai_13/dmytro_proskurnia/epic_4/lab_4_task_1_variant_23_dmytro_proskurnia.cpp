//Проскурня Дмитро ШІ-13

#include <iostream>
#include <ctime>

void printArray(int array[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    srand(std::clock());

    std::cout << "Введіть ваше n: ";
    int n{};
    std::cin >> n;
    if (n < 1 || n > static_cast<int>(1e6)) {
        std::cout << "Неправильний ввід" << std::endl;
        return 1;
    }

    int* array = new int[n];
    for (int i = 0; i < n; i++) {
        array[i] = (rand() % 100) * (rand() % 2 == 0 ? 1 : -1);
    }

    std::cout << "Ваш масив: ";
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Введіть ваше k: ";
    int k{};
    std::cin >> k; k--;
    if (0 > k || k >= n) {
        std::cout << "Неправильний ввід" << std::endl;
        return 1;
    }

    std::cout << "Ваш масив починаючи з k елементу: ";
    for (int i = 0; i < n; i++) {
        std::cout << array[(i + k) % n] << " ";
    }
    std::cout << std::endl;

    int max_element = array[0];
    int count_max_elements{ 1 };
    for (int i = 0; i < n; i++) {
        if (array[i] > max_element) {
            max_element = array[i];
            count_max_elements = 1;
        } else if (array[i] == max_element) {
            count_max_elements++;
        }
    }


    int* new_array = new int[n - count_max_elements];
    int nn = 0;
    for (int i = 0; i < n; i++) {
        if (array[i] != max_element) {
            new_array[nn] = array[i];
            nn++;
        }
    }

    array = new_array;
    new_array = nullptr;
    n = nn;

    std::cout << "Ваш новий масив: ";
    for (int i = 0; i < nn; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Введіть ваше k: ";
    std::cin >> k; k--;
    if (0 > k || k >= n) {
        std::cout << "Неправильний ввід" << std::endl;
        return 1;
    }
    std::cout << "Ваш масив починаючи з k елементу: ";
    for (int i = 0; i < n; i++) {
        std::cout << array[(k - i + n) % n] << " ";
    }
    std::cout << std::endl;

    delete[] array;

    return 0;
}