//Задача №2501 "Симетрична матриця"
#include <iostream>
using namespace std;
char A[1000][1001];
int main() {
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        cin>>A[i];
    }
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if (A[i][j] != A[j][i]){
                cout<<"No"<<endl;
                return 0;
                
            }
        }
    }
    cout<<"Yes"<<endl;
    return 0;
}