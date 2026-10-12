#include <iostream>
using namespace std;
int main() {
    int n, even = 0, odd = 0; 
    cin >> n;
    long long evens[n], odds[n], a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] % 2 == 0) {
            evens[even] = a[i];
            even++;
        } else {
            odds[odd] = a[i];
            odd++;
        }
    }
    if (odd == 1) {
        cout << "YES" << "\n";
        cout << odds[0] << " ";
        for (int i = 0; i < even; i++) {
            cout << evens[i] << " ";
        }
    }
    else cout << "NO" << "\n";
    
}