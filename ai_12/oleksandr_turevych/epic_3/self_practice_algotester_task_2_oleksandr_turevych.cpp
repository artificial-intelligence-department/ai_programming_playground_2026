#include <iostream>
using namespace std; 
int main() {
    int a;
    int b;
    cin >> a;
    cin >> b;
    int count[a];
    for (int i = 0; i < a; ++i) {
        cin >> count[i];
    }
    int currentCount = 0;
    int max = 0;
    for (int i = 0; i < a; ++i) {
        if (count[i] >= b) {
            currentCount++;
            if (currentCount > max) {
                max = currentCount;
            }
        } else {
            currentCount = 0;
        }
    }
    cout << max;
    return 0;
}