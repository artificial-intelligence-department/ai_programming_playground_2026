#include <iostream>
using namespace std;

void checkForFall(char** arr, int n, int m){
    for(int j = 0; j < m; j++){
        int freePosition = n - 1;
        for(int i = n - 1; i >= 0; i--){
            if(arr[i][j] == 'X'){
                freePosition = i - 1; 
            }
            else if(arr[i][j] == 'S'){
                arr[i][j] = 'O';
                arr[freePosition][j] = 'S';
                freePosition--;
            }
        }
    }
}

int main(){

    int n, m;
    cin >> n >> m;
   
    char** cave = new char*[n];            
    for (int i = 0; i < n; ++i)
        cave[i] = new char[m];             

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> cave[i][j];
        }
    }
    checkForFall(cave, n, m);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << cave[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < n; ++i) delete[] cave[i];   
    delete[] cave;

    return 0;
}