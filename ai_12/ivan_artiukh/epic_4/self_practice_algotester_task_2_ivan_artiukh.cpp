//lottery
#include <iostream>
using namespace std;
int main(){
    int n = 0;
    int m = 0;
    cin>>n>>m;
    int arr[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin>>arr[i][j];
        }
    }
    int minMax = 0;
    for(int j = 0, max_curr = 0; j < m; j++){
        for(int i = 0; i < n; i++){
            if( i == 0){
                max_curr = arr[i][j];
                continue;
            }
            if(max_curr < arr[i][j]){
                max_curr = arr[i][j];
            }
        }
        if(j == 0){
            minMax = max_curr;
            continue;
        }
        if(minMax > max_curr){
            minMax = max_curr;
        }
    }

    cout<<minMax<<endl;
}


