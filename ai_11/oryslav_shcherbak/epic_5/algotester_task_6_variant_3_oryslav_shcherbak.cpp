#include <iostream>
using namespace std;

/*
 * Задача: Algotester Lab6v3
 * Щербак Орислав
 * Група ШІ-11
 */

int main(){
    int n;
    cin >> n;
    int** arr = new int*[n];
    for(int i = 0; i < n; i++){
        arr[i] = new int[n];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            char c;
            cin >> c;
            arr[i][j] = c - '0';
        }
    }
    int q;
    cin >> q;
    int* used = new int[n+1];
    for(int i = 0; i < q; i++){
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        if(arr[x][y] != 0){
            cout << "1" << endl;
            cout << arr[x][y] << endl;
            continue;
        }
        for(int i = 0; i<n+1; i++){
            used[i] = 0;
        }
        for(int j = 0; j < n; j++){
            int row = arr[x][j];
            int col = arr[j][y];
            if(row>=1 && row<=n){
                used[row] = 1;
            }
            if(col>=1 && col<=n){
                used[col] = 1;
            }
        }
        int count = 0;
        for(int j = 1; j < n+1; j++){
            if(used[j] == 0){
                count ++;
            }
        }
        cout << count << endl;
        if(count > 0){
            int printed = 0;
            for(int j = 1; j<n+1; j++){
                if(used[j] == 0){
                    if(printed>0){
                        cout << ' ';
                    }
                    cout << j;
                    printed++;
                }
            }
            cout << endl;
        }
    }
    delete[] used;
    for(int i = 0; i<n; i++){
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}