/*
Задача: Лотерея
Карпінський Віталій
ШІ-14
*/
#include <iostream> 
using namespace std;

int main() {
    int n;
    int m;
    cin >> n;
    cin >> m;
    int matrix[n][m] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            cin >> matrix[i][j];
        }
    }
    int collum_max[m];
     for (int j = 0; j < m; j++) {
        int max = matrix[0][j];
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
            }
        
        }
        collum_max[j] = max;
    }

    int collum_min;
    for (int i = 0; i < m; i++) {
        if (i == 0) collum_min = collum_max[i];
        if (collum_min > collum_max[i]) {
            collum_min = collum_max[i];
        }
    }
    cout << collum_min;
    return 0;
}