/*  Lab 1 v3 
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <climits>

using namespace std;

int main() {
long long a; 
long long b = LLONG_MAX;
for(int i = 0; i < 5; i ++ ) {
cin >> a; 
if(a<=0) {
    cout << "ERROR" << endl;
    return 0;
}
    if(a<=b) {
       b = a;
    } 
    else {
        cout << "LOSS" << endl;
        return 0;
    }
}
 cout << "WIN" << endl;
    return 0;
}