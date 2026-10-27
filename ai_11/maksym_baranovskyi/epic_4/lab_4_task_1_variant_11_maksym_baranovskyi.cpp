#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void printArray(int* array, int n) {
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(nullptr));

    const int MAX = 100;
    const int MIN = 1;

    int n;
    cout << "Введіть початковий розмір масиву: ";
    cin >> n;

    int* array = new int[n];
    for (int i = 0; i < n; i++) {
        array[i] = MIN + rand() % (MAX - MIN + 1);
    }

    cout << "Масив з випадкових чисел: " << endl;
    printArray(array, n);
    cout << endl;

    int newN = ((n > 5) ? n - 5 : 0);
    int* temp = new int[newN];

    for (int i = 0; i < newN; i++) {
        temp[i] = array[i];
    }
    
    delete[] array;
    array = temp;   
    n = newN;

    cout << "Масив після видалення 5 елементів: " << endl;
    if (n > 0) {
        printArray(array, n);
    } else {
        cout << "Масив став пустим" << endl;
    }
    cout << endl;
    
    newN = n + 3;
    temp = new int[newN];

    for (int i = 0; i < 3; ++i) {

        int targetIndex = i + 1; 

        if (targetIndex < n) {
            temp[i] = array[targetIndex] + 2;
        } else {
            temp[i] = MIN + rand() % (MAX - MIN + 1);
        }
    }

    for (int i = 0; i < n; i++) {
        temp[i + 3] = array[i];
    }

    delete[] array;
    array = temp;   
    n = newN;

    cout << "Масив після додавання 3 елементів в початок: " << endl;
    printArray(array, n);

    delete[] array;

    return 0;
}
