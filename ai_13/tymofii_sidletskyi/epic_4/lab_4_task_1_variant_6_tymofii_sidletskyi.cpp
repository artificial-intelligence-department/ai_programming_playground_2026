#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace::std;
/* Лаб 4 варіант 6
   Сідлецький Тимофій ШІ-13
*/

void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    const int max_size = 100;
    int arr[max_size];
    int arrsize;
    srand(time(nullptr));

    cout << "Розмір масиву: ";
    cin >> arrsize;

    if (arrsize <= 0 || arrsize >= max_size || cin.fail()) {
        cout << "Некоректний розмір!" << endl;
        return 1;
    }

    for (int i = 0; i < arrsize; ++i) {
        arr[i] = rand() % 100 + 1;
    }

    printArray(arr, arrsize);

    int delete_ind;
    cout << "Введіть номер елемента для знищення: ";
    cin >> delete_ind;
    delete_ind--;

    for (int i = delete_ind; i < arrsize - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arrsize--;

    // додати після першого парного елемента елемент зі значенням M[I-1] + 2
    int even_ind = -1;
    for (int i = 0; i < arrsize; i++) {
        if (arr[i] % 2 == 0) {
            even_ind = i;
            break;
        }
    }
    if (even_ind == arrsize) {
        arrsize++;
    }

    if (even_ind != -1) {
        int newValue = arr[even_ind] + 2; 
        int insert_ind = even_ind + 1;

        for (int i = arrsize; i > insert_ind; i--) {
            arr[i] = arr[i - 1];
        }
        
        arr[insert_ind] = newValue;
        if (even_ind != arrsize) {
            arrsize++;
        }
    } else {
        cout << "Немає парного елемента" << endl;
    }

    printArray(arr, arrsize);

    return 0;
}