#include <iostream>

using namespace std;

int main(){

    int n;
    int count = 0;
    cin >> n;
    char** matrix = new char*[n];
    for (int i = 0; i < n; i++){
        matrix[i] = new char[n];
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (matrix[i][j] == matrix[j][i]){
            count++;
        }
    }
}
    if (count == n*n){
        cout << "Yes";
    }
    else{
        cout << "No";
    }

    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
