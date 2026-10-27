/*  Лабораторна робота 5v7
    Ярошик Наталія
    ШІ-14 */
#include <iostream>
using namespace std;

void changeRowsColumns(int a, int arr[][100]){
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){

            // Перевіряємо збіг перших елементів
            if(arr[i][0] == arr[0][j]){

                // Поелементний обмін
                for(int k = 0; k < a; k++){
                    int temp = arr[i][k];
                    arr[i][k] = arr[k][j];
                    arr[k][j] = temp;
                }
            }
        }
    }
}

int main(){
    int a;
    cout << "Введіть кількість рядків і стовпців: ";
    cin >> a;
    int arr[100][100] = {};

    cout << "Введіть елементи масиву:\n";
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            cin >> arr[i][j];
        }
    }

    changeRowsColumns(a, arr);

    cout << "\nМасив після обміну\n";
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}