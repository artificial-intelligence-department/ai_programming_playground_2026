/*
Lab 4
Лисюк Андріана
ШІ-13
Варіант 11
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    srand(time(0));
    const int N = 100;
    int array[N];
    int size;
    cout << "Введіть початковий розмір масиву (від 5 до " << N << "): ";
    cin >> size;
    if (size < 5 || size > N) {
        cout << "Некоректний розмір! Число має бути від 5 до " << N << "." << endl;
        return 1;
    }
    // Генерація та виведення початкового масиву
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 90 + 10;
        cout << array[i] << " ";
    }
    cout << endl;
    // Знищення 5 останніх елементів
    size -= 5;
    // Додавання 3 елементів у початок за формулою M[I+1]+2
    size += 3;
    for (int i = size - 1; i >= 3; i--) {
        array[i] = array[i - 3];
    }
    for (int i = 2; i >= 0; i--) {
        array[i] = array[i + 1] + 2;
    }
    // Виведення підсумкового масиву
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    return 0;
}