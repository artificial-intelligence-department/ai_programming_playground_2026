#include <iostream>
using namespace std;

int main() {
    int n;
    int m;

    cout << "Введіть n: ";
    cin >> n;

    cout << "Введіть m: ";
    cin >> m;

    // n---m
    int result1 = n-- - m;

    // m--<n
    bool result2 = m-- < n;

    // n++>m
    bool result3 = n++ > m;

    cout << "1) n---m = " << result1 << endl;
    cout << "2) m--<n = " << result2 << endl;
    cout << "3) n++>m = " << result3 << endl;

    return 0;
}