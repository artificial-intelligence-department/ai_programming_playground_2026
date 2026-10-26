/*
Лабораторна робота №4
Варіант 7
Кузовніков В'ячеслав Євгенійович
ШІ-13*/

#include <iostream>
#include <cstdlib> // для rand
#include <ctime> // для time
using namespace std;

int main (){
    srand(time(0));

    int size_arr = 100;
    int current_size = 0;
    size:
    cout << "Введіть розмір масиву від 2 до 100: ";
    cin >> current_size;
    if (cin.fail() || current_size < 2 || current_size > 100){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Неправильний ввід даних. Спробуйте ще раз." << endl;
        goto size;
    }
    cout << "Розмір масиву: " << current_size << endl;


    int arr[size_arr];
    for (int i = 0; i < current_size; i++){
        int random_Number_arr = rand() % 21;
        arr[i] = random_Number_arr;
    }

    cout << "Масив: ";
    for (int i = 0; i < current_size; i++){
        cout << arr[i] << " ";
    }
    int has_zero = 0;
    for (int i = current_size - 1; i >=0; i--){
        
        if (arr[i] == 0) {
            has_zero++;
            int delete_index = i;
            for (int j = delete_index; j < current_size - 1; j++){
                arr[j] = arr [j+1];
            }
            current_size--;
            break;            
        }
    }
    cout << endl;

    if (has_zero == 0){
        cout << "Масив не має нулів." << endl;
    }

    cout << endl;

    cin_index:
    int index;
    cout << "Введіть будь-який індекс від 0 до " << current_size - 1 << ": ";
    cin >> index;
    if (index < 0 || index > current_size -1 || cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Неправильний ввід даних. Спробуйте ще раз." << endl;
        goto cin_index;

    }

    for (int i = current_size -1 ; i > index; i--){
            arr[i + 1] = arr[i];
    }
    arr[index + 1] = 100;
    current_size++;

    cout << "Новий масив: ";
    for (int i = 0; i < current_size; i++){
        cout << arr[i] << " ";
    }

    return 0;
}