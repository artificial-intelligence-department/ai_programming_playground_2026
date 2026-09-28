#include <iostream>
using namespace std;
int main() {
    int a, b;
    cin >> a;
    cin >> b;
    if (0 <= a && a <= 100 && 0 <= b && b <= 100) {
        cout << a + b;
    } else {
        cout << "Числа поза межами діапазону [0, 100]";
    }
    return 0;
}
