/*  
Задача: Algotester Lab 6. Варіант №3.
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <iostream>
#include <string>

using namespace std;

int main() {
int N;
cin >> N;

int** grid = new int*[N];
for (int i = 0; i < N; i++) grid[i] = new int[N];

for (int i = 0; i < N; i++) {
string row;
cin >> row;
    for (int j = 0; j < N; j++) {
        grid[i][j] = row[j] - '0';}}

int Q;
cin >> Q;

int* used = new int[N + 1];
for (int q = 0; q < Q; q++) {
int x, y;
cin >> x >> y;
x--;
y--;

if (grid[x][y] != 0) {
cout << 1 << "\n" << grid[x][y] << "\n";
continue;}

for (int d = 1; d <= N; d++) used[d] = 0;

for (int i = 0; i < N; i++) {
int valRow = grid[x][i];
if (valRow >= 1 && valRow <= N) used[valRow] = 1;

int valCol = grid[i][y];
if (valCol >= 1 && valCol <= N) {
used[valCol] = 1;}}

int count = 0;
for (int d = 1; d <= N; d++) {
if (used[d] == 0) {
count++;}}

cout << count << "\n";
if (count > 0) {
    for (int d = 1; d <= N; d++) {
        if (used[d] == 0) {
            cout << d << " ";}}
            cout << endl;}}

delete[] used;
for (int i = 0; i < N; i++) {
    delete[] grid[i];}

delete[] grid;

    return 0;
}
