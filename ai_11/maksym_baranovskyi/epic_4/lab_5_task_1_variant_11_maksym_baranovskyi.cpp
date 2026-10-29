#include <iostream>

using namespace std;

int checkSort(int** array, int row, int m){
    bool ascending = true, descending = true;

    for(int j = 0; j < m - 1; j++){
        if(array[row][j] > array[row][j+1]){
            ascending = false;
        }
        if(array[row][j] < array[row][j+1]){
            descending = false;
        }
    }

    if(ascending){
        return 1;
    }
    if(descending){
        return -1;
    }
    return 0;
}

void sortRows(int** array, int n, int m){
    for(int i = 0; i < n; i++){
        int checkedSort = checkSort(array, i, m);
        if(checkedSort == 1){
            continue;   
        }
        for(int k = 0; k < m - 1; k++){
            for(int j = 0; j < m - 1 - k; j++){
                if(array[i][j] > array[i][j+1]){
                    int temp = array[i][j];
                    array[i][j] = array[i][j+1];
                    array[i][j+1] = temp;
                }
            }
        }
    }
}

void freeArray(int**& array, int rows){
    for(int i = 0; i < rows; i++){
        delete[] array[i];
        array[i] = nullptr;
    }
    delete[] array;
    array = nullptr;
}

int main(){

    cout << "Введіть кількість рядків та стовпців: " << endl;
    int n, m;
    if(!(cin >> n >> m) || n < 1 || m < 1){
        cout << "Введено некоректне значення!" << endl;
        return 1;
    }

    int** array = new int*[n];
    for(int i = 0; i < n; i++){
        array[i] = nullptr;  
    }

    cout << "Введіть елементи масиву: " << endl;

    for(int i = 0; i < n; i++){
        array[i] = new int[m];
        for(int j = 0; j < m; j++){
            if(!(cin >> array[i][j])){
                cout << "Введено некоректне значення!" << endl;
                freeArray(array, n);
                return 1;
            }
        }
    }

    cout << "Введіть номер рядка для перевірки на сортування (від 1 до " << n << "): " << endl;
    int row;
    if(!(cin >> row) || row < 1 || row > n){
        cout << "Некоректний номер рядка!" << endl;
        freeArray(array, n);
        return 1;
    }

    int rowResult = checkSort(array, row - 1, m);

    if(rowResult == 1) cout << "Впорядкований за зростанням" << endl;
    else if(rowResult == -1) cout << "Впорядкований за спаданням" << endl;
    else cout << "Невпорядкований" << endl;

    sortRows(array, n, m);

    cout << "Результат після сортування: " << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    freeArray(array, n);

    return 0;
}