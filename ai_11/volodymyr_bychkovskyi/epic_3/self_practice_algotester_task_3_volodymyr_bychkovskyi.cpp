/*
Назва: Непередбачувана погода
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int temp[n];
    for (int i = 0; i < n; i++) {
        cin >> temp[i];
    }
    for (int i = 0; i < n; i++) {
        if(temp[i] > 0) {
            cout << i+1 << " ";
        }
    }
     
    return 0;
}