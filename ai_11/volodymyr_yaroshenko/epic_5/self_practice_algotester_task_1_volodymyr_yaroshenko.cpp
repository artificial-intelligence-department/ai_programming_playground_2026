/*  
Self Practice завдання 1
Ярошенко Володимир 
11 група 
*/
#include <iostream>
using namespace std;

int main() {
long n =0 ,m = 0;
string s;
string t;
cin >> n >> m;
cin >> s >> t;
long all = (n+1)*(m+1);
long s4=0, t4=0, s7=0, t7=0;
for(int i=0; i<n;i++) {
    if(s[i] == '4') s4++;
    else s7++;
}
for(int i=0; i<m; i++) {
    if(t[i] == '4') t4++;
    else t7++;
}
long rem = (s4*t4) + (t7*s7);
long res = all - rem - 1;
cout << res; 
    return 0;
}