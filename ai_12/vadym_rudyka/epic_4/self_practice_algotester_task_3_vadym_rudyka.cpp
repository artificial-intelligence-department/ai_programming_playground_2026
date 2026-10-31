#include <iostream>
#include <cmath>
using namespace std;

int main(){

    long long n = 0, m = 0;
    cin >> n >> m;

    const long long N = n;
    const long long M = m;
    long long a[N][M];
    long long temp = 0;
    long long col = 0;
    long long max = 0;
    long long real_col = 0;

// записую елементи матриці
    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            cin >> a[i][j];
        }
    }
// шукаю стовпець з найменшим максимальним елементом
    for (int j = 0; j<m; j++){
    temp = a[0][j];
        for (int i = 0; i<n; i++){
            if (a[i][j]>temp){
                temp = a[i][j];
                col = j;
            }
        }
    if (j == 0 || temp < max) {
        max = temp;
        real_col = j;
    }

    }
    temp = a[0][real_col];
// шукаю максимальний елемент у стовпці, де знаходиться мінімальний елемент
    for (int i = 0; i<n; i++){
        if (a[i][real_col]>temp){
            temp = a[i][real_col];
        }
    }
    cout << temp;
    }

