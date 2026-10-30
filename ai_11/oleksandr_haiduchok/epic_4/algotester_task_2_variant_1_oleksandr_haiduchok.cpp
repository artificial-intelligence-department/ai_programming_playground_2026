#include <iostream>

using namespace std;

int main(){
    int N = 0;
    int m = 0;
    cin >> N;
    int r[N];
    
    for(int i = 0; i < N; i++){
        cin >> r[i];
    }
    if(N <= 2){
        cout << "0";
        return 0;
    }
    int temp = 0;
    for(int j = 0; j < N - 1; j++){
        for(int v = 0; v < N - j - 1; v++){
            if(r[v] > r[v + 1]){
                temp = r[v];
                r[v] = r[v + 1];
                r[v + 1] = temp;
            }
        }
        
    }
        int m1 = r[N - 1] - r[1];
        int m2 = r[N - 2] - r[0];
        if(m2 < m1){
            cout << m2;
        }
        else{
            cout << m1;
        }
    
    return 0;
}
