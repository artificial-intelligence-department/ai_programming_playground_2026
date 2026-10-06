#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;

    if (a > b)
    {
        cout << b*b << endl;
        return 0;
    }
    cout << a*a << endl;
    return 0;
}