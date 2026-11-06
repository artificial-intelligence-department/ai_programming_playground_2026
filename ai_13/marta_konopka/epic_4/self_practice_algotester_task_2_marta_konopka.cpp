// "Симетрична матриця"
#include<iostream>
using namespace std;

const int MAX_N = 1000;
char a[MAX_N][MAX_N];

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    bool isSymmetric = true;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(a[i][j] != a[j][i]){
                isSymmetric = false;
                break;
            }
        }
        if(!isSymmetric){
            break;
        }
    }
    if(isSymmetric){
        cout << "Yes";
    }
    else{
        cout << "No";
    }

        return 0;

}
