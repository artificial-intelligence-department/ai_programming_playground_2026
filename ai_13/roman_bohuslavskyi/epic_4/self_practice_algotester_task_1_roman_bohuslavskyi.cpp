/*
Задача:  Непарний масив
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int a[100000];
    int result[100000];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int oddCount = 0;
    int evenCount = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) evenCount++;
        else oddCount++;
    }
    
    if (evenCount > oddCount+1 || oddCount > evenCount+1) {
        cout << -1;
        return 0;
    }
    
    int evenPos;
    int oddPos;

    if (evenCount >= oddCount) {
        evenPos = 0;
        oddPos = 1;
    } 
    else {
        evenPos = 1;
        oddPos = 0;
    }
    
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            result[evenPos] = a[i];
            evenPos += 2;
        }
        else {
            result[oddPos] = a[i];
            oddPos += 2;
        }
    }
    
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
}