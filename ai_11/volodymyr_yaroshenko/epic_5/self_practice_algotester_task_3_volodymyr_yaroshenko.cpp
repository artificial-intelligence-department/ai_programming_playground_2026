/*  
Self Practice завдання 3
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
string s, t;
cin >> s >> t;
int n = s.size();
char a[100001];
bool position[100001] = {};
int res[100001];
int j = 0;
for (int i =0; i< n;i++) {
    a[i] = s[i];
    if (j< n && s[i]==t[j]) {
        position[i] = true;
        j++;
    }
}
int len = n;
int count = 0;
for (int i= j; i< n;i++) {
    for (int k =0; k <len;k++) {
        if(position[k] == false && a[k] == t[i]) {
            res[count] = k + 1;
            count++;
        for (int x = k; x < len - 1; x++) {
            a[x] = a[x + 1];
                position[x] = position[x + 1];
            }
            len--;
       break;
    }
    }
}
    cout << count << '\n';
    for (int i= 0;i<count;i++) {
        cout << res[i] << ' ';
    }
    return 0;
}