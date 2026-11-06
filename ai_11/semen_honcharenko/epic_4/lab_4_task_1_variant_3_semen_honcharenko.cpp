/*
    Лабораторна робота 4. Завдання 1. Варіант 3.
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
#include <cstdlib> // for random
#include <ctime> // for random
using namespace std;

int main() {
    srand(time(nullptr)); // for random
// Step 1
    int arr[105];
    int size = 0;

    cout << "Кількість чисел: ";
    while (!(cin >> size) or size < 1 or size > 100) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error. size must be between 1 and 100\n";
        cout << "Кількість чисел: ";
    }
    
    for (int i = 0; i < size; ++i) {
        *(arr+i) = -10 + (rand() % 21); // filling array with random numbers [-10; 10]

// Step 2
        if (i > 0) {
            cout << " ";
        }
        cout << *(arr+i);
    }
    cout << "\n";

// Step 3
    int new_size = 0;
    for (int i = 0; i < size-1; ++i) {
        for (int j = 0; j < size-1; ++j) {
            if (*(arr+j) == 0) {
                *(arr+j) = *(arr+j+1);
                *(arr+j+1) = 0;
            }
        }
    }
    for (int i = 0; i < size; ++i) {
        if (*(arr+i) == 0) {
            break;
        }
        new_size++;
    }
    if (new_size == 0) {
        cout << "All elements are zero. Array is empty." << "\n";
        return 0;
    }
// Step 4
    int temp = 0;
    int stop = -1;
    for (int i = 0; i < new_size; ++i) {
        if (*(arr+i) % 2 == 0) {
            stop = i;
            break;
        }
    }
    if (stop == -1) {
        cout << "No even numbers" << "\n"; // no even numbers
        new_size -= 1;
    }
    if (stop != -1) {
    int end = new_size;
    while (end > stop) {
        *(arr+end+1) = *(arr+end);
        end--;
    }
    if (stop == 0) {
        *(arr+stop+1) = *(arr+stop)+2;
    }
    else {
        *(arr+stop+1) = *(arr+stop-1)+2;
    }
    }
// Step 5
    for (int i = 0; i < new_size+1; ++i) {
        if (i > 0) {
            cout << " ";
        }
        cout << *(arr+i);
    }
    cout << "\n";
}