/*
    Задача: портрет
    Михайловська Анна
    ШІ-14
*/

#include <iostream>

using namespace std;

int main (){

    int n, m, k;
    char a[1000][1000];

    cin >> n >> m >> k;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }

    int result = 0;
    for (int i = 0; i < n; i++) {

        int stars = 0;

        for (int j = 0; j < m; j++) {
            if ( a[i][j] == '*')
                stars +=1;  
        }
        
        if ((stars % k) == 0)
            result += stars / k;
        else
            result += (stars / k) + 1;
    }

    cout << result;

    return 0;
}
