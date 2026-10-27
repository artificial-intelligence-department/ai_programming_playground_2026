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
    for(int i = 0; i < n - 1; i++){
        int checkedSort = (array, i, m);
        if(checkedSort == -1){
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

int main(){

    cout << "Введіть кількість рядків та стовпців: " << endl;
    int n, m;
    cin >> n >> m;

    int ** array = new int*[n];

    cout << "Введіть елементи масиву: " << endl;

    for(int i = 0; i < n; i++){
        array[i] = new int[m];
        for(int j = 0; j < m; j++){
            cin >> array[i][j];
        }
    }

    cout << "Введіть номер рядка для перевірки на сортування: " << endl;
    int row;
    cin >> row;

    int rowResult = checkSort(array, row + 1, m);

    if(rowResult == 1) cout << "Впорядкований за зростанням" << endl;
    else if(rowResult == -1) cout << "Впорядкований за спаданням" << endl; 
    else cout << "Невпорядкований" << endl;

    sortRows(array, n, m);

    cout << "Результат після сортування: ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << array[i][j] << " ";
        cout << endl;
    }

    for(int i = 0; i < n; i++){
        delete[] array[i];
    }
    delete[] array;

    return 0;
}