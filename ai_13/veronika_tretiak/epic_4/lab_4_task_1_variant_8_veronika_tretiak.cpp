/*
Автор: Вероніка Третяк
Задача: Лабораторна робота  №4
Група: ШІ-13
*/
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
    int n;
    cout << "Введіть розмір масиву: " << endl;
    if(!(cin >> n) || n < 1 || n > 100){
        cout << "Помилка: Введіть число від 1 до 100." << endl;
        return 1;
    }

    srand(time(nullptr));
    int* arr = new int[n];

    cout << "Початковий масив: " << endl;
    for(int i = 0; i < n; i++){
        arr[i] = rand() % 10;
        cout << arr[i] << " ";
    }
    cout << endl;

    int value;
    cout << "Яке значення видалити?: "<< endl;
    if(!(cin >> value)){
        cout << "Помилка введення.";
        delete[] arr;
        arr = nullptr;
        return 1;
    }
    int count = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] != value){
            arr[count] = arr[i];
            count++;
        }
    }
    n = count;
    int Zerocount = 0;
    for(int i = 0 ; i < n; i++){
        if(arr[i] % 2 == 0){
            Zerocount++;
        }
    }
    int newSize = n + Zerocount;
    int* result = new int[Zerocount];
    int j = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] % 2 == 0){
            result[j] = 0;
            j++;
        }
        result[j] = arr[i];
        j++;
    }
    cout << "Отриманий масив: " << endl;
    if(newSize == 0){
        cout << "Порожній" << endl;
    }
    for( int i = 0; i < newSize; i++){
        cout << result[i] << " ";
    }
    cout << endl;

    delete[] arr;
    arr = nullptr;
    delete[] result;
    result = nullptr;

    return 0;


}