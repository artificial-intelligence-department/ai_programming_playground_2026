#include<iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;

    int mn, mx;
    if (a < b) {
        mn = a;
        mx = b;
    } else {
        mn = b;
        mx = a;
    }
    
    if (mx - mn > 1) {
        cout << mn + 1;
    } else {
        cout << -1 ;
    }
      return 0;
}