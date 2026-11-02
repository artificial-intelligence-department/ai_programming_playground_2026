/*
lab5  task 1 variant 7, Андрій Мадяр
*/
#include <iostream>
using namespace std;
void swapLines(int n, int **arr){//функція заміни, масив передано як параметр
     for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            if(arr[i][0] == arr[0][j]){//умова заміни рядка і стовпця
                for(int k = 0; k<n; k++){
                    int temp = arr[i][k];
                    arr[i][k] = arr[k][j];
                    arr[k][j] = temp;
                }
                break;//верне назад якщо не закрити цикл j
            }
        }
    }
    for(int i = 0; i<n; i++){//вивід нової множини
        for(int j = 0; j<n; j++){
            cout << arr[i][j] << "\t";
        }
        cout << "\n";
    }
}
int main(){
    int n=0;
    cout << "Введіть кількість рядків і стовпців(одне додатнє число): ";
while(!(cin >> n) || n < 1){//ввід розміру
        cout << "Введіть додатнє ЧИСЛО: \n";
        cin.clear();
        cin.ignore(100, '\n');
    }
    int **arr = new int*[n];//динамічний двовимірний масив
    for(int i = 0; i<n; i++){
        arr[i] = new int[n];
    }
    for(int i = 0; i<n; i++){//ввід елементів
        for(int j = 0; j<n; j++){
            cin >> arr[i][j];
        }
    }
    cout << "До обміну:\n";
    for(int i = 0; i<n; i++){//вивід старої версії
        for(int j = 0; j<n; j++){
            cout << arr[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "Після обміну:\n";
    swapLines(n, arr);
    for(int i = 0; i<n; i++){//видалення динамічного масиву
        delete[] arr[i];
        arr[i] = nullptr;
    }
    delete[] arr;
    arr = nullptr;
    return 0;
}