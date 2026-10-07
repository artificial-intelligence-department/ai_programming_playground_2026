#include <iostream>
using namespace std;
//задача 2251
int main() {
    int n,m,k;
    cin >> n >> m >> k;
    if (n * m % k == 0) {
        cout << "Yes";
    } else {
        cout << "No";
    }

    return 0;
}