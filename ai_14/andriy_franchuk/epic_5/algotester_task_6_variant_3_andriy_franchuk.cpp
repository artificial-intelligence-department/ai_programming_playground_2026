#include <iostream>

using namespace std;

int main() {
    int N, Q;
    cin >> N;

    int arr[N][N];

    for(int i = 0; i < N; i++){
        int row = 0;
        cin >> row;
        for(int j = N-1; j >= 0; j--){
            arr[i][j] = row % 10;
            row = row / 10;
        }
    }

    cin >> Q;

    int x[Q];
    int y[Q];


    for(int i = 0; i < Q; i++){
        cin >> x[i];
        cin >> y[i];
    }

    for(int i = 0; i < Q; i++){
        if(arr[x[i]-1][y[i]-1] != 0){
            cout << 1 << endl;
            cout << arr[x[i]-1][y[i]-1] << endl;
            cout << endl;
            continue;
        }
        int counter = 0;
        int possible[N];
        for(int i = 0; i < N; i++){
            possible[i] = i + 1;
        }

        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                if(k == (y[i]-1)){
                    continue;
                }
                if(possible[j] == arr[x[i]-1][k]){
                    possible[j] = 0;
                }
            }
            for(int k = 0; k < N; k++){
                if(k == (x[i]-1)){
                    continue;
                }
                if(possible[j] == arr[k][y[i]-1]){
                    possible[j] = 0;
                }
            }
        }

        for(int i = 0; i < N; i++){
            if(possible[i] != 0){
                counter += 1;
            }
        }
        cout << counter << endl;

        for(int i = 0; i < N; i++){
            if(possible[i] != 0){
                cout << possible[i] << " ";
            }
        }
        cout << endl;
        cout << endl;
    }
}