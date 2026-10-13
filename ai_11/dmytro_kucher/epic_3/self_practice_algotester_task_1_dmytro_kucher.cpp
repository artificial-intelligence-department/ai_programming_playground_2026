/*
Епік 3. Self Practice: Algotester, задача "Поле чудес"
Автор: Кучер Дмитро
Група: ШІ-11
*/ 

#include<iostream>
#include<string>
using namespace std;

int main () {

    string s; cin >> s;
    if (s.length()<0 || s.length()>100) return 1;
    short sameL = 0;
    
    for (int i = 0; i<s.length(); i++) {

        for (int j = 0; j<i; j++) {
            if (s[i] == s[j]) {
                sameL++;
                break;
            }
        }
    }

    cout << s.length() - sameL;

    return 0;
}