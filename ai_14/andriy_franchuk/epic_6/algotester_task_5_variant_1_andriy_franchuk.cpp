#include <iostream>
#include <cmath>

using namespace std;

int main(){
    unsigned long long a, N, R[1000], C[1000], a_bit[8][8];
    cin >> a >> N;

    for(int i = 0; i < N; i++){
        cin >> R[i] >> C[i];
        R[i]--;
        C[i]--;
    }

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            a_bit[i][j] = a%2;
            a = a/2; 
        }
    }

    for(int i = 0; i < N; i++){
        if(a_bit[R[i]][C[i]]){
            a_bit[R[i]][C[i]] = 0;
        }else{
            a_bit[R[i]][C[i]] = 1;
        }
        for(int j = 0; j < 8; j++){
            if(C[i] != j){
                if(a_bit[R[i]][j]){
                    a_bit[R[i]][j] = 0;
                }else{
                    a_bit[R[i]][j] = 1;
                }
            }
            if(R[i] != j){
                if(a_bit[j][C[i]]){
                    a_bit[j][C[i]] = 0;
                }else{
                    a_bit[j][C[i]] = 1;
                }
            }
            
        }
    }

    a = 0;
    unsigned long long t = 1;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            a += a_bit[i][j]*t;
            t = t*2;
        }
    }

    cout << a;
}