#include <iostream>

using namespace std;
int main(){
    int N = 0;
    int M = 0;
    cin >> N >> M;
    char arr[N][M];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> arr[i][j];
        }
    }

    for(int j = 0; j < M; j++){
        int pos = N - 1;
    for(int i = N - 1; i >= 0; i--){
        if(arr[i][j] == 'X'){
        pos = i - 1;
    }
    else if(arr[i][j] == 'S'){
        arr[i][j] = 'O';
        arr[pos][j] = 'S';
        pos--;
     }
    }
} 
    
for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
        cout << arr[i][j];
    }
    cout << "\n";
}
   
return 0;
}