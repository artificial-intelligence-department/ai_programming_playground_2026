/* 
Задача: Algotester Self-Practice №2.
Автор: Дячок Маргарита.
Група: ШІ-14
*/

#include <iostream>
using namespace std;

int main() {
int n;
cin >> n;
if (n < 1 || n > 8) return 0;

int* ferz = new int[n];
for (int i = 0; i < n; i++) ferz[i] = -1;

int count = 0;
int row = 0;

while (row >= 0) {
    ferz[row]++; 
    if (ferz[row] >= n) {
    ferz[row] = -1; 
    row--;               
    continue;}

int place = 1;
for (int i = 0; i < row; i++) {
    int rizni_row = row - i;
    int rizni_col = ferz[row] - ferz[i];
            
if (rizni_col == 0 || rizni_col == rizni_row || rizni_col == -rizni_row) {
place = 0;
break;}}
        
if (place == 1) {
if (row == n - 1) {
count++; 
} else {
row++;}}}

cout << count << endl;

delete[] ferz; 
return 0;
}
