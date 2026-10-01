#include <iostream>

using namespace std;

int main() {
int a,b,c, res;
cin >> a >> b >> c;

if(a<1 || a > 5000) {
    return -1;
}
if(b < 1 || b > 5000) {
    return -1;
}
if(c < 1 || c >100 ) {
    return -1;
}

if(a>=b) {
    cout << a << endl;
}
else {
cout << (a +c) << endl;
}


    return 0;
}