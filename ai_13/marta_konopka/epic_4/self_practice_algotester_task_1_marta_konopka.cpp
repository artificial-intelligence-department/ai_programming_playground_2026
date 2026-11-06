// "Зеник-садівник"
#include<iostream>
using namespace std;

const int MAX_N = 100;
const int MAX_M = 100;

int main(){
    int n, m;
    if(!(cin >> n >> m)){
        return 0;
    }

    char arr[MAX_N][MAX_M];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if((i + j / 2) % 2 == 0){
                arr[i][j] = 'x'; 
            }
            else{
                arr[i][j] = 'o';
            }
            }
        }
         for(int i = 0; i < n; i++){
          for(int j = 0; j < m; j++){
            cout << arr[i][j];
    }
    cout << "\n";
}
  return 0;
}