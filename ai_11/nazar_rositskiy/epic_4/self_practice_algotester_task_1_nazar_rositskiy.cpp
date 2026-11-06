#include <iostream>
#include <map>

using namespace std;

int main() {

    int n;
    cin >> n;
    char matrix[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> matrix[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(matrix[i][j] != matrix[j][i]){
                cout << "No";
                return 0;
            }
        }
    }
    cout << "Yes";
    
}
