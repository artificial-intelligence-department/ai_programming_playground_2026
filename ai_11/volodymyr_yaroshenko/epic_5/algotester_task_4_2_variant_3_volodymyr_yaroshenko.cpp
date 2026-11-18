/*  
Algotester 4
Варіант 3(без STL) 
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <algorithm>
using namespace std;
int partition(int* a, int low, int high, bool rev) {
int pivot = a[high];
int i = low - 1; 
for (int j = low; j < high; j++) {
    if (rev ? (a[j] >= pivot) : (a[j] <= pivot)) {
            i++;
            swap(a[i], a[j]);
        }
}
swap(a[i + 1], a[high]);
return i + 1;
}
void quickSort(int* arr, int low, int high, bool rev) {
if (low < high) {
        int pi = partition(arr, low, high, rev);
        quickSort(arr, low, pi - 1, rev);
        quickSort(arr, pi + 1, high, rev);
    }
}
int* duplicates(int* a, int& size) {
int uniqueCount = 1;
for (int i = 1; i < size; i++) {
    if (a[i] != a[uniqueCount - 1]) {
        a[uniqueCount] = a[i];
        uniqueCount++;
    }
}
int* na = new int[uniqueCount];
for (int i = 0; i < uniqueCount; i++) {
    na[i] = a[i];
}
delete[] a;
size = uniqueCount;
return na;
}
int main() {
int n =0;
int n1 = 0, n2 = 0 , n3 = 0;
int j=0, k=0, l=0;
cin >> n;
int* a = new int[n]; 
for(int i =0; i<n; i++){
cin >> a[i];
}

int* p1 = new int[1000];
int* p2 = new int[1000];
int* p3 = new int[1000];

for(int i=0; i<n;i++){
if(a[i] % 3 ==0) {
n1++;
p1[j] = a[i];
j++;
}
if(a[i] % 3 ==1) {
n2++;
p2[k] = a[i];
k++;
}
if(a[i] % 3 ==2) {
n3++;
p3[l] = a[i];
l++;
}
}
bool rev = false;
quickSort(p1, 0, n1-1, rev);
quickSort(p3, 0, n3-1, rev);
quickSort(p2, 0, n2-1, true);

p1 = duplicates(p1, n1);
p2 = duplicates(p2, n2);
p3 = duplicates(p3, n3);

cout << n1 + n2 + n3 << endl;
for(int i=0; i<n1; i++){
    cout << p1[i] << ' ';
}
for(int i=0; i<n2; i++){
    cout << p2[i] << ' ';
}
for(int i=0; i<n3; i++){
    cout << p3[i] << ' ';
}
delete[] p1;
delete[] p2;
delete[] p3;
    return 0;
}