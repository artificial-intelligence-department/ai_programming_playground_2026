/*
Algotster Lab 3v3, Нагірний Назарій, ШІ-13
*/
#include <iostream>
using namespace std;
int main(){
   string s;
   cin >> s;
int n = s.length();
    for (int i = 0; i < n; i++) {
        int count = 1; 
        while (i + 1 < n && s[i] == s[i + 1]) {
            count++;
            i++;
        }
        cout << s[i];
        if (count > 1) {
            cout << count;
        }
    }
    return 0;
}