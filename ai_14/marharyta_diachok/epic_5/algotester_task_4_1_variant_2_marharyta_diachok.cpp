/*  
Задача: Algotester Lab 4(1). Варіант №2.
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
int N, K;
cin >> N >> K;
if (N <= 0) {
cout << 0 << endl;
return 0;}

int* a = new int[N];

for (int i = 0; i < N; i++) {cin >> a[i];}

sort(a, a + N);

int n = 0;
for (int i = 0; i < N; i++) {
if (i == 0 || a[i] != a[i - 1]) {
    a[n] = a[i];
    n++;}}

while (K >= n) {
    K -= n;}

cout << n << endl;

for (int i = K; i < n; i++) {
    cout << a[i] << " ";}
for (int i = 0; i < K; i++) {
    cout << a[i] << " ";}

delete[] a;

    return 0;
}
