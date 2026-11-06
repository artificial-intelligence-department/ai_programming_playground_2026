/*
Лабораторна робота №4, Завдання 1, Варіант 7
Станіслав Коваль
ШІ-12
*/

#include <iostream>
#include <random>
using namespace std;

int main () {
    int n;
    cout << "ВВедіть кількість елементів масиву: ";
    cin >> n;
    int* arr = new int[n];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(-10, 10);
    for (int i = 0; i < n; i++) {
        arr[i] = distrib(gen);
    }

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int zeroIndex = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] == 0) {
            zeroIndex = i;
            break;
        }
    }

    int* newArr = new int[n - 1];
    if (zeroIndex == -1) {
        cout << "Елемента, що дорівнює 0, у масиві немає." << endl;
    } 
    else {
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (i != zeroIndex) {
                newArr[j++] = arr[i];
            }
        }
        delete[] arr;
        arr = newArr;
        n--;
        cout << "Масив після видалення останнього нуля: ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    cout << "Введіть індекс елемента, після якого потрібно вставити 100: ";
    int index;
    cin >> index;
    if (index < 0 || index >= n+1) {
        cout << "Індекс виходить за межі масиву." << endl;
        return 1;
    }

    newArr = new int[n + 1];
    int j = 0;
    for (int i = 0; i < n; i++) {
        newArr[j++] = arr[i];
        if (i == index-1) {
            newArr[j++] = 100;
        }
    }
    delete[] arr;
    arr = newArr;
    n++;

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;
}