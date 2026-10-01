#include <iostream>

using namespace std;

int main() {
int a, b;
cin >> a >> b;
if(a<0 || a>100 ) {
    return -1;
}
if(b<0 || b>100 ) {
    return -1;
}
cout << (a + b) << endl;

    return 0;
}