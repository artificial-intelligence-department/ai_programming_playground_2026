/*  
Algotester 2
Варіант 1 
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <climits>
using namespace std;

int main() {
int n;
int m =0;
int m_min;
int m_max;
int min, mmin, min_i =0;
int max, mmax, max_i= 0;
cin >> n;
int* a =new int[n];
for(int i =0; i<n; i++) {
    cin >> a[i];
}
if(n ==1) {
    cout << m;
    return 0;
}
//Перевіркаа на мінімум та максимум для початкового масиву 
min = a[0];
max =a[0];
for(int i =1;i<n; i++) {
    if(a[i] < min){
 min_i = i;
        min =a[i];
    }
}

for(int i =1;i<n; i++) {
    if(a[i] > max){
 max_i = i;
        max =a[i];
    }
}
// Створення нового масиву
int* b = new int[n-1];
int min_index = 0;
for(int i =0; i<n; i++) {
    if(min_i == i) {
        continue;
    }
b[min_index] = a[i];
min_index++;
}

int* c = new int[n-1];
int max_index = 0;
for(int i =0; i<n; i++) {
    if(max_i == i) {
        continue;
    }
c[max_index] = a[i];
max_index++;
}
delete[] a;
a = nullptr;
//Перевірка на мінімум  та максимум нового масиву
min = b[0];
max = b[0];
for(int i =0; i<n-1; i++) {
if(b[i] < min){
    min =b[i];
    }
    if(b[i]> max) {
    max = b[i];
}
}
mmin = c[0];
mmax = c[0];
for(int i =0; i<n-1; i++) {
if(c[i] < mmin){
    mmin =c[i];
    }
    if(c[i]> mmax) {
    mmax = c[i];
}
}
delete[] b;
b = nullptr;
delete[] c;
c = nullptr;
m_min = max - min;
m_max = mmax -mmin;
//Вивід результату 
if(m_min == m_max) {
    cout << m_min;
}
if(m_min>m_max) {
    cout << m_max;
}
if(m_min<m_max) {
    cout << m_min;
}
    return 0;
}