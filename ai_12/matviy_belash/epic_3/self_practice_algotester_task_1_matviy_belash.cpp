/*
Белаш Матвій ШІ-12
Завдання з алготестеру "Зуби"
*/
#include <iostream>
#include <utility>
using namespace std;

int main(){

    int n, k;
    cin >> n >> k;
    int a[n];
    int kl = 0;
    int max = 0;

    for(int i = 0; i <n; i++){
        cin >> a[i];
    }

    for(int i = 0; i < n; i++){
        if(a[i] >= k){
            kl += 1;
            if(kl > max){
                max = kl;
            }
        } else{
            kl = 0;
        }
    }

    cout << max;

    return 0;
}