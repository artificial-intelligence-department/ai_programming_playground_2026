/*  
Self practice algotester 2
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <cmath>
using namespace std;

int main() {
long  a, b, c,  res = 0;
cin >> a >> b; 
if((b -a) % 12 == 0) {
    res = ((a + b) * 13) / 2;

cout << res << endl;
}
else {
    cout << "-1" << endl;
}
return 0;
}