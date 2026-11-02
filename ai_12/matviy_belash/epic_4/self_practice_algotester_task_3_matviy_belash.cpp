/*
Белаш Матвій ШІ-12
Завдання з алготестеру "Літня школа"
*/
#include <iostream>
using namespace std;

int main(){

    int n=0, k=0;
    cin >> n >> k;

    if(n>(k*3) || n < k){
        cout << "Impossible";
        return 0;
    }

    int m = 0;

    if(n % k == 0){
        m = n / k;
    }else m = (n/k) + 1;

    int a[k];
    for(int i=0; i<k; i++){
        a[i] = 0;
    }
    for(int i=1; i<=m; i++){
        for(int j=0; j<k; j++){
            a[j]++;
            n--;
            if(n==0){
                for(int u=0; u<k; u++){
                    cout << a[u] << " ";
                }
                return 0;
            }
        }
    }
}