#include <iostream>
using namespace std;
int main () {
    int n;
    cin >> n;
    bool ans = true;
    char matr[1000][1000];
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j< n; j++) {
           cin >> matr[i][j]; 
        }
    }
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j< n; j++) {
        if (matr[i][j] != matr[j][i]) {
        ans = false;
        } 
        }
    }
    if (ans) {
        cout << "Yes";
    } else {
        cout << "No";
    }    
}
