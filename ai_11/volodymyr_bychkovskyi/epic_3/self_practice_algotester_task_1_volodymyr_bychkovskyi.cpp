/*
Назва: Зуби
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
using namespace std;

int main(){
    long long  n, k;
    int a=0, b=0;
    cin >> n;
    cin >> k;
    long long arr[n];
    for (int i = 0; i<n; i++){
        cin >> arr[i];
      
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] >= k) {
            a++;
            if (a > b) {
                b = a;
            }
        } else {
            a = 0;
        }
    }
    cout << b;

    return 0;
}