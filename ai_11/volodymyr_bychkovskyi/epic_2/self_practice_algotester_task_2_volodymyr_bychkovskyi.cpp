/*
Назва: self practice | Шоколадка
Автор: Бичковський Володимир
Група: ШІ-11
*/

#include <iostream>
using namespace std;
int main(){
    int n, m, k, s;
    cin >> n >> m >> k;
    s = n*m;
    if(s%k==0){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
}