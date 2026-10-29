/*  
Self Practice завдання 2
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
int n, m;
cin >> n >> m;
int total = n * m;
int* arr = new int[total];
for (int i = 0; i < total; i++) {
    cin >> arr[i];
}
sort(arr, arr + total);
int k = 0;
for (int i = 0; i < total; i++) {
    if (i > 0 && arr[i] == arr[i - 1]) {
            k++;
    }
}
cout << k << endl;
for (int i = 0; i < total; i++) {
    if (i > 0 && arr[i] == arr[i - 1]) {
            cout << arr[i] << " ";
    }
}
cout << endl;
delete[] arr;
return 0;
}