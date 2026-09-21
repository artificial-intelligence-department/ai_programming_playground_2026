#include<iostream>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    if( a + c <= b ) {
        cout << "ALL";
        return 0;
    }
    if( a <= b ) {
        cout << "All registered";
        return 0;

    }
    else {
        cout << "Bad organizers";
    }
    return 0;

}