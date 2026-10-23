#include <iostream>
using namespace std;

int main(){

    int n, m;
    cin >> n;
    int a[n];

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    cin >> m;
    int b[m];
    for(int i = 0; i < m; i++){
        cin >> b[i];
    }

    int same = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(a[i] == b[j]){
                same++;
            }
        }
    }
    cout << same << endl;
    cout << (n+m)-same;

    return 0;
} 