/*
Назва: Лотерея
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int m;
    cin >> m;
    int arr[n][m];

    for(int i=0; i<n; i++){
        for(int j = 0; j<m; j++){
            cin >> arr[i][j];
        }
    }
    int minMax = 0;
    bool is = true;
     for(int i=0; i<m; i++){
        int a = 0;
        for(int j = 0; j<n; j++){
            if(arr[j][i]>a){
                a = arr[j][i];
            }
            
        }
        if(is){
            minMax = a;
            is = false;
        }
        if(minMax>a){
            minMax = a;
        }
    }
    cout << minMax;
}