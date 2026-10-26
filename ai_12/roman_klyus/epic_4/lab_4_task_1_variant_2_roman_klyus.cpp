#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(-20, 20);

    const int max_size = 100;
    int mas[max_size];
    int size;
    cout << "Ввeдіть довжину масиву від 1 до " << max_size << ": ";
    cin >> size;

    for (int i = 0; i < size; i++) {
        *(mas + i) = distrib(gen);
    }

    cout << "Отиманий масив:" << endl;
    for (int i = 0; i < size; i++) {
        cout << *(mas + i) << " ";
    }


    int del_idx = -1;

    for (int i = 0; i < size; i++) {
        if (*(mas + i) == 0) {
            del_idx = i;
            break;
        }
    }

    int count;
    if (del_idx != -1) {
        for (int i = del_idx; i < size - 1; i++) *(mas + i) = *(mas + i + 1);
        size--;
        cout << "\nЕлемент 0 з індексом " << del_idx << " видалено\n";
    } else {
        cout << "\nЕлементів зі значенням 0 не знайдено\n";
    }

    for (int i = 1; i < size; i++) {
        if (*(mas + i) % 2 == 0) {

            if (size >= max_size) {
                cout << "\nМи досягнули максимального розміру масиву (" << max_size << "), більше елементів додати не можна\n";
                break;
            }

            int new_el = *(mas + i - 1) + 2;

            for (int j = size; j > i + 1; j--) {
                *(mas + j) = *(mas + j - 1);
            }
            *(mas + i + 1) = new_el;
            size++;
            i++;
            count++;
            cout << "Додали елемент " << setw(3) << new_el << " в комірку з індексом " << i << endl;
        }
    }
    cout << "Загалом додано елементів: " << count << endl;
    cout << "Отиманий масив:" << endl;
    for (int i = 0; i < size; i++) {
        cout << *(mas + i) << " ";
    }

}

