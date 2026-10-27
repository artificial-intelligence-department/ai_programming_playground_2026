/*
Лабораторна робота №5
Варіант 7
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
using namespace std;

void change_rows_and_columns(int **mas, int n) {
    bool swapped = false;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            
            if (i != j && mas[i][0] == mas[0][j]) {
                cout << "Міняємо місцями " << i + 1 << "-й рядок та " << j + 1 << "-й стовпець:" << endl << endl;
              
                for (int k = 0; k < n; k++) {
                    int temp = mas[i][k];
                    mas[i][k] = mas[k][j];
                    mas[k][j] = temp;
                }

                swapped = true;
                break; 
            }
        }
        if (swapped){
            break;
        }  
    }

    if (!swapped) {
        cout << "Рядків та стовпців з однаковими першими елементами не знайдено." << endl << endl;
    }

  
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << mas[i][j] << "\t";
        }
        cout << endl;
    }
}

int main (){
    size_rows:
    int rows = 0;
    cout << "Введать кількість рядків двовимірного масиву: " ;
    cin >> rows;
    if (cin.fail() || rows < 2 || rows > 10){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Неправильний ввід даних. Спробуйте ще раз." << endl;
        goto size_rows;
    }

    cout << endl;

    size_columns:
    int columns = 0;
    cout << "Введіть кількість стовпців двовимірного масиву: ";
    cin >> columns;
    if (cin.fail() || columns < 2 || columns > 10){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Неправильний ввід даних. Спробуйте ще раз." << endl;
        goto size_columns;
    }

    cout << endl;

    int** arr = new int*[rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[columns];
    }

    cout << "Введіть елементи масиву: " << endl;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            cin >> arr[i][j];
        }
    }
    cout << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }

    cout << endl;

    if (rows != columns){
        cout << "Двовимфрний масив не квадратний, отже міняти місцями стовпці та рядки ми не можемо" << endl;
    }
    else {
        change_rows_and_columns(arr, rows);
    }



    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;


    return 0;
}