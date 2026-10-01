/*  
Self practice algotester 1
Ярошенко Володимир 
11 група 
*/
#include <iostream>
using namespace std;

int main() {
int n, m, k;
cin >> n >>  m >> k;

if((n || m) <1 || (n || m) >100) {
    return -1;
}
else if( k <1 || k> 10000) {
    return -1;
}
if((n * m) % k == 0) {
    cout << "Yes" << endl;
    return 0;
}
else {
    cout << "No" << endl;
}
    return 0;
}