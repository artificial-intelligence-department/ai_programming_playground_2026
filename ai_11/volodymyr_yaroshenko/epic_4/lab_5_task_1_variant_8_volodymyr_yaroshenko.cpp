/*  
Лабораторна 5 завдання 1
Варіант 8
Ярошенко Володимир 
11 група 
*/
#include <iostream>
using namespace std;
const int MAX = 5;
int sym_count =0;
bool sym = false;
void trans(int a[MAX][MAX]) {
    int b[MAX][MAX] = {};
for(int i =0; i<MAX; i++) {
 for(int j=0; j<MAX; j++) {
    b[i][j] = a[i][j];
 }
}
 for(int i =0; i<MAX; i++) {
    for (int j = i + 1; j < MAX; j++) {
    int temp = a[i][j];
    a[i][j] = a[j][i];
    a[j][i] = temp;
  }
 }

 for(int i =0; i<MAX; i++) {
    for(int j=0; j<MAX; j++) {
        if(a[i][j] == b[i][j]){
            sym_count++;
        }
    }
}
if(sym_count == MAX * MAX) {
 sym = true;
}
}

int main() {
int a[MAX][MAX] = {};
cout << "Введіть матрицю:(розмір 5х5)" << endl;
for(int i =0; i<MAX; i++) {
    cout << "Введіть " << i+1 << " рядок" << endl;
    for(int j =0; j<MAX; j++) {
 cin >> a[i][j];
    }
}
cout << "Початкова матриця: " << endl;
for(int i =0;i <MAX; i++){
    for(int j=0; j<MAX; j++) {
        cout << a[i][j] << " ";
    }
    cout << endl;
 }
trans(a);
cout << "Транспонована матриця: " << endl;
for(int i =0;i <MAX; i++){
    for(int j=0; j<MAX; j++) {
        cout << a[i][j] << " ";
    }
    cout << endl;
 }
 cout <<"Симетричність:  "<< boolalpha << sym << endl;
    return 0;
}