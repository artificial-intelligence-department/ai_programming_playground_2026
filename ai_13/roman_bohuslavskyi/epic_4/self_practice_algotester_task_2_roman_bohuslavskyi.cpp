/*
Задача:  Дракон і кросворд
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
   int n,m;
   cin >> n >> m;
   char a[100][100];
   
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < m; j++) {
           cin >> a[i][j];
       }
   }
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < m; j++) {
            bool repeated = false;
            for (int k = 0; k < m; k++) {
                if (a[i][k] == a[i][j] && k != j) {
                    repeated = true;
                    break;
                }
            }
            for (int k = 0; k < n; k ++) {
                if (a[k][j] == a[i][j] && k != i) {
                    repeated = true;
                    break;
                }
            }
            if (!repeated) {
                cout << a[i][j];
            }
        }
    }
}