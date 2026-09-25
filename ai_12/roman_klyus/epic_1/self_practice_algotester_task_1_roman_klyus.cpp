#include <iostream>

using namespace std;

int main() {
    
    long long res = 0;
    int n;
    cin >> n;

    int* a = new int[n];

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    for (int i = 0; i < n; ++i) {
        res += a[i]-1;
    }

    cout << res << endl;
    return 0;
}