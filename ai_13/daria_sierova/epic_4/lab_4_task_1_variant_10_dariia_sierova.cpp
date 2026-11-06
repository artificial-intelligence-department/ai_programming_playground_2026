#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void printarr(const int* arr, int size){
    for (int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0)); // ініціалізація генератор випадкових числа

    int size; //початковий ромір
    cout << "Введіть розмір масиву: ";
    cin >> size;

    if(cin.fail()) return 0;

    if ( size < 5){
        cout << "Помилка, розмір масиву має бути не менше 5." << endl ;
        return 0;
    }

    int* arr = new int[size];
    // заповнюєм масив
    for ( int i = 0; i < size; i++){
        arr[i] = rand()%100 + 1; //діапазон від 1 до 100
    }

    // початковий масив
    cout << "Початковий масив (" << size << " елементів):";
    printarr(arr, size);

    // знищуєм 5 перших ел
    int k = 5;
   
    int newSize = size - k;
    int* temp = new int[newSize];        // копіюєм ел починаючи з 5 індексу
    for (int i = 0; i < newSize; i++){ 
        temp[i] = arr[i + k];
    }

    delete[] arr;
    arr = temp; // перенаправляємл arr на новий масив temp(адреса temp)
    size = newSize;

    cout << "Після видалення перших " << k << " елементів: ";
    printarr (arr, size);

    //додаємо 3 ел
    int add_k = 3;
    newSize += add_k;
    temp = new int[newSize];
    // копіюєм ел
    for (int i = 0; i < size; i++){
        temp[i] = arr[i];
    }
    // додаємо 3 випадкові
    for (int i = size; i < newSize; i ++){
        temp[i] = rand() % 100 + 1;
    }

    delete[] arr;
    arr = temp;
    size = newSize;

    cout << "Після додавання " << add_k << " нових елементів в кінець: ";
    printarr(arr, size);

    delete[] arr;

    return 0;
}