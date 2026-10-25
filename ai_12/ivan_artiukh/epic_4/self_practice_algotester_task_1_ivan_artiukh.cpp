//danger
#include <iostream>
#include <string>
using namespace std;
int main(){
    int n = 0;
    int m = 0;
    cin>>n>>m;
    int **arr = new int*[n];
    for(int i = 0; i < n; i++){
        arr[i] = new int[m];
        string tmp = "";
        cin >> tmp;
        for(int j = 0; j < m; j++){
            arr[i][j] = tmp[j] - 48;
        }
    }
    bool isAnsw = true; 
    for(int i = 0; i < n; i++){
        int sum = 0;
        for(int j = 0; j < m; j++){
            sum += arr[i][j];
        }
        if(sum == 0){
            isAnsw = false;
        }
    }
    if(isAnsw){
        cout << "YES";
        return 0;
    }
    isAnsw = true;
    for(int i = 0; i < m; i++){
        int sum = 0;
        for(int j = 0; j < n; j++){
            sum += arr[j][i];
        }
        if(sum == 0){
            isAnsw = false;
        }
    }
    if(isAnsw){
        cout << "YES";
    }
    else{
        cout << "NO";
    }
    for(int i = 0; i < n; i++){
        delete[] arr[i];
    }
    delete[] arr;
    arr = nullptr;
}


