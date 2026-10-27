/* 
Задача: Лабораторна робота №5. Завдання 1. Варіант №2. 
Автор: Дячок Маргарита.
Група: ШІ-14
*/

#include <iostream>
using namespace std;

void Swap(int** m, int cols, int e1, int e2) {
    for(int j = 0; j < cols; j++){
    int temp = m[e1][j];
    m[e1][j] = m[e2][j];
    m[e2][j] = temp;}}

int main() {
int rows;
int cols;
cin >> rows >> cols;
int** m = new int*[rows];
for(int i = 0; i < rows; i++) {
m[i] = new int[cols];}

for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
    cin >> m[i][j]; }}

cout << endl;

for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
    cout << m[i][j] << " ";}
    cout << endl;}

for(int i = 0; i < rows - 1; i++) {
    for(int j = 0; j < rows - i - 1; j++) {
if(m[j][2] > m[j + 1][2]) {
    Swap(m, cols, j, j + 1);}}}

cout << endl;

for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
    cout << m[i][j] << " "; }
    cout << endl;}

for(int i = 0; i < rows; i++) {
    delete[] m[i];}
    delete[] m;
    return 0;

}