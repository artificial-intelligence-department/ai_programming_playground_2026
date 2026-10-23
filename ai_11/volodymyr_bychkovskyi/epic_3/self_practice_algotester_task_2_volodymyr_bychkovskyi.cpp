/*
Назва: Складний екзамен
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
using namespace std;

int main(){
    string n;
    cin >> n;

    for(int i=0; i + 1 < n.length(); i++){
        if (n[i] == '4' && n[i+1] == '7') {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}