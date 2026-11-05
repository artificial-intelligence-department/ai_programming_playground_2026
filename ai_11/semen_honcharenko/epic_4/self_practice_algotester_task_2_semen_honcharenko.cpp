/*
    Алготестер. "Halloween"
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
using namespace std;

int main() {
    int n = 0;
    int m = 0;
    cin >> n;
    cin >> m;
    int zenik_price[n] = {};
    int marie_price[m] = {};
    int zenik_min = 0;
    int marie_min = 0;
    
    for (int i = 0; i < n; i++) {
        cin >> zenik_price[i];
        if (i == 0) {
            zenik_min = zenik_price[i];
        }
        if (zenik_min > zenik_price[i]) {
            zenik_min = zenik_price[i];
        }
    }
    for (int i = 0; i < m; i++) {
        cin >> marie_price[i];
        if (i == 0) {
            marie_min = marie_price[i];
        }
        if (marie_min > marie_price[i]) {
            marie_min = marie_price[i];
        }
    }
    cout << zenik_min + marie_min;
    return 0;
}