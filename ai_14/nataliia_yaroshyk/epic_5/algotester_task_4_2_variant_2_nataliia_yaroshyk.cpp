#include <iostream>
using namespace std;

int main(){
    int N, K;
    cin >> N >> K;
    int a[N] = {};
    for(int i = 0; i < N; i++){
        cin >> a[i];
    }

    for(int i = 0; i < N; i++){
        for(int j = i + 1; j < N; j++){
            if(a[i] == a[j]){
                for(int k = j; k < N - 1; k++){
                    a[k] = a[k+1];
                }
                N--;
                j--;
            }
        }
    }

    for(int i = 0; i < N - 1; i++){
        for(int j = 0; j < N - 1; j++){
            if(a[j] > a[j + 1]){
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    K = K % N;

    for(int i = 0; i < K; i++){
        int first = a[0];
        for(int j = 0; j < N - 1; j++){
            a[j] = a[j + 1];
        }
        a[N - 1] = first;
    }

    cout << N << "\n";
    for(int i = 0; i < N; i++){
        cout << a[i] << " ";
    }
    return 0;
}