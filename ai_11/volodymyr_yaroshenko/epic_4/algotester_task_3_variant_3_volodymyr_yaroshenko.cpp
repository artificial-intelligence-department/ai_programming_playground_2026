/*  
Algotester 3
Варіант 3 
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
string s;
cin >> s;
int i = 0;
while (i < s.length()) {
    char ch = s[i];
    int count = 0;
while (i < s.length() && s[i] == ch) {
        count++;
        i++;
}
cout << ch;
    if (count > 1) {
        cout << count;
   }
}
    return 0;
}
