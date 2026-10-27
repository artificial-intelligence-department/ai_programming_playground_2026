#include <iostream>
using namespace std;

int main() {
    int n, k; 
    cin >> n >> k;
    if (n < k || n > 3*k) {
        cout << "Impossible\n";
        return 0;
    }
    int a[k];
    int sum = 0;
    for (int i = 0; i < k; i++) {
        a[i] = 0;   
    }
    while (sum < n) {
        for (int i = 0; i < k; i++) {
            a[i] += 1;
            sum += 1;
            if (sum == n) break; 
        }
    } 
    for (int i = 0; i < k; i++) {
        cout << a[i] << " ";
    } 
}