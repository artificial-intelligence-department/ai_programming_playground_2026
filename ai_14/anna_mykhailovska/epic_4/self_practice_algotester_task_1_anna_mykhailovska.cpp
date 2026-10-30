/*
    Задача: лотерея
    Михайловська Анна
    ШІ-14
*/

#include <iostream>

using namespace std;

int main(){
    int n, m, a[1000][1000];

    cin >> n >> m;

    for (int i =0; i<n; i++){
        for (int j =0; j<m; j++){
            cin >> a[i][j];
        }
    }

    int answear = 1001;
    for (int i =0; i<m; i++){
        int max = a[0][i];
        for (int j=0; j<n; j++){
            if (a[j][i] > max)
            max = a[j][i]; 
        }

        if (max < answear)
        answear = max;
    }

    cout << answear;

    return 0;

}

