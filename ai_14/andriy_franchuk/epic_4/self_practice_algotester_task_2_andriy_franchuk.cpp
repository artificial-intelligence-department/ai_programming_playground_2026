/*Epic 4 - Зеник-садівник
Франчук Андрій
Ші - 14*/
#include <iostream>

using namespace std;

int main(){
    int m, n;
    cin >> n >> m;

    char a[n][m];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i%2 == 0){
                if(j % 4 < 2){
                    a[i][j] = 'x';
                }else{
                    a[i][j] = 'o';
                }
            }else{
                if(j % 4 < 2){
                    a[i][j] = 'o';
                }else{
                    a[i][j] = 'x';
                }
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << a[i][j];
        }
        cout << endl;
        
    }
}