#include <iostream>
#include <string>

using namespace std;

int main(){
    int N,Q,x,y;
    cin >> N;

    int *res = new int[N+1];
    for(int i = 0; i < N+1; i++){
        res[i] = i;
    }

    int** matrix = new int*[N];
    for(int i = 0; i < N; i++){
        matrix[i] = new int[N];
    }

    for(int i = 0; i < N; i++){
        string temp;
        cin >> temp;
        for(int j = 0; j < N; j++){
            matrix[i][j] = temp[j] - '0';
        }
    }

    cin >> Q;

    for(int i = 0; i < Q; i++){
        cin >> x >> y;
        x--;
        y--;
        if(matrix[x][y] != 0){
            cout << 1 << endl << matrix[x][y] << endl << endl;
            continue;   
        }
        for(int j = 0; j < N; j++){
            res[matrix[x][j]] = 0;
        }
        for(int j = 0; j < N; j++){
            res[matrix[j][y]] = 0;
        }

        int count = 0;
        for(int i = 1; i < N+1; i++){
            if(res[i] != 0){
                count++;
            }
        }

        cout << count << endl;
        for(int i = 1; i < N+1; i++){
            if(res[i] != 0){
                cout << res[i] << " ";   
            }
            else{
                res[i] = i;
            }
        }

        cout << endl << endl;
    }

    delete[] res;

    for(int i = 0; i < N; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}