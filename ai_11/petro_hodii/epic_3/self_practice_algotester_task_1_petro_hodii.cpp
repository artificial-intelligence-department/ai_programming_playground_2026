#include <iostream>

using namespace std;

int main(){
    int n,m;
    int a1;
    int a2;
    int min1 = 1000;
    int min2 = 1000;

    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> a1;
        if(a1 < min1){
            min1 = a1;
        }
    }
    for(int i = 0; i < m; i++){
        cin >> a2;
        if(a2 < min2){
            min2 = a2;
        }
    }

    cout << (min1 + min2);

    return 0;
}