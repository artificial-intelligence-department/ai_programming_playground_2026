#include <iostream>
using namespace std;
int main(){
    const int M = 100000;
    int a[M];
    int n = 0;
    while(cin >> a[n]){
        n++;
    }
    if(n < 1){
        return 0;
    }
    
    int temp = 0;
    for(int j = 0; j < n - 1; ++j){
        for(int l = 0; l < n - j - 1; ++l){
            if(a[l] > a[l + 1]){
            temp = a[l];
            a[l] = a[l+1];
            a[l+1] = temp;
            }
        }
    }
    for(int x = 0; x < n; x++){
        cout << a[x];
        if (x + 1 < n) {
            cout << " ";
        }
    }
    return 0;
}
