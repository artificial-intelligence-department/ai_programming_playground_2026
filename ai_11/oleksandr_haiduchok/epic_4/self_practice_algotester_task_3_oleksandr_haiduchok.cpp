#include <iostream>
using namespace std;
int main(){
    int n = 0;
    cin >> n;
    char **matrix = new char*[n];
    for(int s = 0; s < n; s++){
        matrix[s] = new char[n];
        for(int d = 0; d < n; d++){
            cin >> matrix[s][d];
        }
    }
    bool flag = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(matrix[i][j] != matrix[j][i]){
                flag = false;
            }
        }
    }

    if(flag == false){
        cout << "No";
    }
    else{
        cout << "Yes";
    }
    for(int g = 0; g < n; g++){
        delete[] matrix[g];
    }
    delete[] matrix;
    matrix = nullptr;
    return 0;
}