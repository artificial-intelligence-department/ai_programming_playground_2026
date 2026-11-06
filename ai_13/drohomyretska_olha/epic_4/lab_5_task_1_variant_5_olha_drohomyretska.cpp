/*
Задача: Лабораторна робота 5. 
Варіант: 5
Автор: Дрогомирецька Ольга, ШІ-13
*/
#include <iostream>
using namespace std;

void deleteRow(int mas[][20], int rows, int cols, int row) { //функція видаляє один рядок, нижчі зсуває вгору, останній заповнює нулями
    //зсуваємо наступні рядки вгору
    for (int i = row; i < rows - 1; i++) {
        for (int j = 0; j < cols; j++) {
            mas[i][j] = mas[i + 1][j];
        }
    }
    //заповнюємо останній рядок нулями
    for (int j = 0; j < cols; j++) {
        mas[rows - 1][j] = 0; 
    }
}
int main () {
    int mas[20][20];
    int rows, cols;

cout << "Введіть кількість рядків і стовпців (1-20): ";
if (!(cin >> rows >> cols) || rows < 1 || rows > 20 || cols < 1 || cols > 20) {
    cout << "Неправильні розміри масиву." << endl;
    return 1; 
}
cout << "Введіть елементи масиву:" << endl;
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        if (!(cin >> mas[i][j])) {
            cout << "Помилка введення." << endl;
            return 1; 
        }
    }
}
cout << "Початковий масив:" << endl;
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        cout << mas[i][j] << " ";
    }
    cout << endl;
}
int A, B;
cout << "Введіть номери рядків A і B для видалення: ";
if (!(cin >> A >> B) || A < 1 || B > rows || A > B) {
    cout << "Потрібно: 1 <= А <= В <= кількість рядків." << endl;
    return 1;
}
for (int k = 0; k < B - A + 1; k++) {
    deleteRow(mas, rows, cols, A - 1); //видаляємо рядок A-1 (індексація з 0)
}
//rows не зменшуємо, шоб вивести також звільнені рядки з нулями
cout << "Масив після видалення рядків:" << endl;
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        cout << mas[i][j] << " ";
    }
    cout << endl;
}
return 0;
}