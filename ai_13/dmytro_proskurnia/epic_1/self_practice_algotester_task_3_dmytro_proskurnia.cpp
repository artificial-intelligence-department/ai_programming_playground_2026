// 0921
#include <iostream>

using namespace std;

signed main()
{
    int a, b; cin >> a >> b;
    if (a > b) {
        int c = a;
        a = b;
        b = c;
    }
    if (a + 1 >= b) {
        cout << -1;
    } else {
        cout << a + 1;
    }

    return 0;
}
