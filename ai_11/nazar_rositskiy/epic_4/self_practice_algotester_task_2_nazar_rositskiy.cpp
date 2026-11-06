#include <iostream>
#include <algorithm>

using namespace std;

int main() {


    int rows, cols;
    cin >> rows >> cols;
    int matrix[rows][cols];
    int arr[rows*cols];
    int n = rows*cols;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cin >> matrix[i][j];
        }
    }
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            arr[cols*i + j] = matrix[i][j];
        }
    }

    sort(arr, arr+n);
    cout << endl;
    int res = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] == arr[i-1]){
            res++;
        }
    }

    cout << res << endl;

    for(int i = 0; i < n; i++){
        if(arr[i] == arr[i-1]){
            cout << arr[i] << " ";
        }
    }
    


}
