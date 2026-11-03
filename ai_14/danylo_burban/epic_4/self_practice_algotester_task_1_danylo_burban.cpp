/*Epic 4 - Лотерея
Бурбан Данило
Ші - 14*/
#include <iostream>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    int **arr = new int*[n];
    for(int i = 0; i < n; i++){
        arr[i] = new int[m];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> arr[i][j];
        }
    }

    int result;

    for(int j = 0; j < m; j++){
        int col_max = arr[0][j];
        for(int i = 1; i < n; i++){
            if(arr[i][j] > col_max){
                col_max = arr[i][j];
            }
        }
        if(j == 0 || col_max < result){
            result = col_max;
        }
    }

    cout << result;
    for(int i = 0; i < n; i++){    
        delete[] arr[i];
        arr[i] = nullptr;
    }
    delete[] arr;

    return 0;
}