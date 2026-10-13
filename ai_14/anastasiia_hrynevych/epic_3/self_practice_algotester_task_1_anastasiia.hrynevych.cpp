#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    
    int n, x; cin >> n >> x;
    int count = 0;
    int a[n], copy[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        copy[i] = a[i];
    }
    sort(copy, copy + n, greater<int>());
        for (int i = 0; i < n; i++) {
            if (copy[i] >= 10) {
                count++;
            }
            if (copy[i] < 10) {
                x = x - (10 - copy[i]);
                count++;
                if (x == 0) break;
                if (x < 0) {
                    count--;
                    break;
                }
            }
            
    }
    cout << count << endl;
    
}