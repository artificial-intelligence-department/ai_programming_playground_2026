/*
Задача: Lab 4v2 (no stl)
Виконав: Сукач Андрій (ШІ-14)
*/
#include <iostream>

using namespace std;

int main(){
    int n,k;
    cin >> n >> k;
if (cin.fail() || n < 1 || n > 1000 || k < 1 || k > 1000) return 1;

int a[1001] = {0};
for (int i = 0; i < n; i++){
    cin >> a[i];
}

  for (int j = 0; j < n - 1; ++j){//сортую бульбашкою
    for (int i = 0; i < n - 1 - j; ++i){
        if (a[i] > a [i + 1]){
        int temp = a[i];
        a[i] = a[i + 1];
        a[i + 1] = temp;
        }
      }
   }
int u[1001] = {0}; // унікальний
int newSize = 0;
   for (int i = 0; i < n; i++){
    if (i == 0 || a[i] != a[i-1]){
        u[newSize] = a[i];
        newSize++;
    }
   }

    
for (int j = 0; j < k; j++){
    int swap = u[0];
   for (int i = 0; i < newSize - 1; i++){
    u[i] = u[i + 1];
   }
   u[newSize- 1] = swap;
}
cout << newSize << endl;
for (int i = 0; i < newSize; i++){
    cout << u[i] << " ";
}

return 0;
}