/*  
Задача: Algotester Lab 4(2). Варіант №2.
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <iostream>

using namespace std;

int main() {
int N, K;
cin >> N >> K;
int* a = new int[N];
for (int i = 0; i < N; i++) cin >> a[i];

for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < N - i - 1; j++) {
        if (a[j] > a[j + 1]) {
            int temp = a[j];
            a[j] = a[j + 1];
            a[j + 1] = temp;}}}

int n = 0;
for (int i = 0; i < N; i++) {
    if (i == 0 || a[i] != a[i - 1]) {
        a[n] = a[i];
        n++;}}

while (K >= n) K -= n;

cout << n << endl;

for (int i = K; i < n; i++) cout << a[i] << " ";
for (int i = 0; i < K; i++) cout << a[i] << " ";

delete[] a;

    return 0;
}
