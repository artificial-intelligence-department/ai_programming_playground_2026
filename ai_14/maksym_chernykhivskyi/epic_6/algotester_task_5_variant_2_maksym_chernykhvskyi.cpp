/*Epic 6 - lab 5v2
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

void collapseSand(char **cave, int N, int M, int i, int j){
    for (int k = i; k < N - 1; k++){
        if (cave[k+1][j] == 'O'){
            cave[k][j] = 'O';
            cave[k+1][j] = 'S';
        } else {
            break;
        }
    }
}

void collapseCave(char **cave, int N, int M){
    for (int i = N - 1; i >= 0; i--){
        for (int j = M - 1; j >= 0; j--){
            if (cave[i][j] == 'S'){
                collapseSand(cave, N, M, i, j);
            }       
        }
    }
} 

int main(){
    int N, M;
    cin >> N >> M;
    
    char **cave = new char*[N];
    for (int i = 0; i < N; i++){
        cave[i] = new char[M];
    }
    
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> cave[i][j];
        }
    }
    collapseCave(cave, N, M);
    
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cout << cave[i][j];
        }
        cout << "\n";
    }
    
    for (int i = 0; i < N; i++){
        delete[] cave[i];
    }
    delete[] cave;
    
}