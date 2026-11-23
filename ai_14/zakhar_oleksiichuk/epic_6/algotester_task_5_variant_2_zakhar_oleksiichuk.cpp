#include <iostream>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    
    char matrix[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> matrix[i][j];
        }
    }
    
    for (int j = 0; j < M; j++) {
        int write = N-1;
        for (int i = N-1; i >= 0; i--) {
            if (matrix[i][j] == 'X') {
                write = i-1;
                continue;
            }
            if (matrix[i][j] == 'S') {
                matrix[i][j] = 'O';
                matrix[write][j] = 'S';
                write = write-1;
                continue;
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
    
}
