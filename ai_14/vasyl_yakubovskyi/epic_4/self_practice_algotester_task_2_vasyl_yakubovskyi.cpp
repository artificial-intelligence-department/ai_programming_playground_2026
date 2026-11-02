/*
Task: self_practice_algotester_task_2 (Симетрична матриця)
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/


#include <iostream>

using namespace std;

const int MAX = 1000;

int main (){

    int n = 0;
    cin >> n;
    if(n < 1 || n > 1000){
        return 0;
    }
    char a[MAX][MAX];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
        }

    }

    bool issymetric = true;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(a[i][j] != a[j][i]){
                issymetric = false;
            }
        }

    }

    cout << (issymetric ? "Yes" : "No") << endl;

    return 0;
}