/*  Algotester self practice
    "Симетрична матриця"
    Ярошик Наталія
    ШІ-14 */
#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    char arr[n][n] = {};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> arr[i][j];
        }
    }
    bool isSymmetric = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(arr[i][j] != arr[j][i]) isSymmetric = false;
        }
    }
    if(isSymmetric){
        cout << "Yes";
    }else{
        cout << "No";
    }
    return 0;
}