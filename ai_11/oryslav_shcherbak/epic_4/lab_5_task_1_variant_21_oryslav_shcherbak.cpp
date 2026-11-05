#include <iostream>
using namespace std;

/*
 * Задача: Lab 5 Task 1-21
 * Щербак Орислав
 * Група ШІ-11
 */

void findMaxRepeated(int** arr, int rows, int cols){
    int count = 0;
    bool found = false;
    int maxRepeated = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            count = 0;
            for(int k = 0; k < rows; k++){
                for(int l = 0; l < cols; l++){
                    if(arr[i][j] == arr[k][l]){
                        count++;    
                    }
                }
            }
            if(count > 1 && (!found || arr[i][j] > maxRepeated)){
                maxRepeated = arr[i][j];
                found = true;
            }
        }
    }
    if(found){
        cout << "Максимальний повторювальний елемент: " << maxRepeated << endl;
    }
    else{
        cout << "Повторбваних елементів немає." << endl;
    }
}
int main(){
    int rows, cols;
    cout << "Введіть кількість рядків і стовпців: ";
    if(!(cin >> rows >> cols) || rows <= 0 || cols <= 0){
        cout << "Помилка вводу." << endl;;
        return 1;
    }
    int** arr = new int*[rows];
    for(int i = 0; i < rows; i++){
        arr[i] = new int[cols];
    }
    cout << "Введіть елементи масиву: " << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(!(cin >> arr[i][j])){
                cout << "Помилка вводу." << endl;
                for(int k = 0; k < rows; k++){
                    delete[] arr[k];
                }
                delete[] arr;
                return 1;
            }
        }
    }
    findMaxRepeated(arr, rows, cols);
    for(int k = 0; k < rows; k++){
        delete[] arr[k];
    }
    delete[] arr;
    return 0;
}