/* 
Задача: Algotester Self-Practice №3.
Автор: Дячок Маргарита.
Група: ШІ-14
*/

#include <iostream>
using namespace std;

int main() {
int n, m;
cin >> n >> m;
    
int** bilet = new int*[n];
for(int i = 0; i < n; i++) {
    bilet[i] = new int[m];}
    
for(int i = 0; i < n; i++) {
for(int j = 0; j < m; j++) {
    cin >> bilet[i][j];}}

int min; 
int bilet_cols = 0;
int bilet_rows = 0;

for(int j = 0; j < m; j++) {
    int current_max = bilet[0][j];
    int current_max_row = 0;
        
for(int i = 1; i < n; i++) { // Цикл строго до n (кількість рядків)
if(bilet[i][j] > current_max) {
    current_max = bilet[i][j];
    current_max_row = i;}}

       
if(j == 0) {
    min = current_max;
    bilet_cols = j;
    bilet_rows = current_max_row;} 
else {
if(current_max < min) {
    min = current_max;
    bilet_cols = j;
    bilet_rows = current_max_row;}}}

cout << bilet[bilet_rows][bilet_cols] << endl;

for(int i = 0; i < n; i++) {
    delete[] bilet[i];}
delete[] bilet;

    return 0;
}
