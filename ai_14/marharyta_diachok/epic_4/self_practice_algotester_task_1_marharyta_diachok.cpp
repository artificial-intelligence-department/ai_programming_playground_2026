/* 
Задача: Algotester Self-Practice №1.
Автор: Дячок Маргарита.
Група: ШІ-14
*/

#include <iostream>
using namespace std;
int main() {
int n, k;
cin >> n >> k;
int* m = new int[k];
if(n < k || n > 3 * k) {cout << "Impossible"; return 0;}
else {
    for(int i = 0; i < k; i++) m[i] = 1;
int zalyshok = n - k;
for(int i = 0; i < k; i++) {
    while (m[i] < 3 && zalyshok > 0) {
    m[i]++;
    zalyshok--;
}}}

for(int i = 0; i < k; i++) {
    cout << m[i] << " ";
}


delete[] m;

    return 0;
}