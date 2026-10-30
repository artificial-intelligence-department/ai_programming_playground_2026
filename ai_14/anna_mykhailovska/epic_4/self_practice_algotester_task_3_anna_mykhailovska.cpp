/*
    Задача: Замовлення від стоматологів
    Михайловська Анна
    ШІ-14
*/

#include <iostream>

using namespace std;

int main (){

    int n;

    cin >> n;

    char a[2][1000];

    bool tooth = false;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    for (int j = 0; j < n; j++) {
        if (a[0][j] == '1' && a[1][j] == '1') {
            tooth = true;
            break;
        }
    }

    cout << (tooth ? "Yes" : "No");
    
    return 0;
}
