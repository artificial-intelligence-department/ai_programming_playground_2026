#include <iostream>
using namespace std;
char a[1001][1001];
int main(){
    int n, m;
    cin>> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for(int j = 0; j < m; j++) {
        int pos =n - 1;
        for(int i = n-1; i>=0; i--){
            if (a[i][j] == 'X') {
                pos = i - 1;
            } else if (a[i][j]== 'S') {
                a[i][j] ='O';
                a[pos][j]= 'S';
                pos--;
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << a[i][j];
        }
        cout<< "\n";
    }
}