/*
self practice task 3, Складний екзамен
*/
#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    bool passed = false;
    while(n > 0){
    if(n % 100 == 47){//перевірка самої умови
        passed = true;
        break;
    }
    n /= 10;//зсув для подальшої перевірки
    }
    if(passed)cout << "YES";
    else cout << "NO";
    return 0;
}