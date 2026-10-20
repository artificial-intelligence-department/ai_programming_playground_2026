#include <iostream>
using namespace std; 
int main() {
    int a;
    cin >> a;
    int count[a];
    for (int i = 0; i < a; ++i) {
        cin >> count[i];
    }
    long long sum = 0;
    int b = 0;
    for (int i = 0; i < a; ++i) {
        if (count[i] < 2) {
            continue;
        }
        sum += count[i];
        b++;
    }
    cout << sum-b;
    return 0;
}