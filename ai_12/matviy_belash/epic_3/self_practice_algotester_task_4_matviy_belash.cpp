/*
<Белаш Матвій ШІ-12
Завдання з алготестеру "Поле чудес"
*/

#include <iostream>
#include <string>
using namespace std;
int main(){

    string s;
    cin >> s;
    int n = s.size();
    char a[n];
    int u = n;

    for(int i = 0; i < n; i++){
        a[i] = s[i];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(j > i){
                if(a[i] == a[j]){
                    u -= 1;
                    break;
                }
            }
        }
    }
    cout << u;

    return 0;

}