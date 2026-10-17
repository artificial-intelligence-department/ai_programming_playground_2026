#include <iostream>
using namespace std;

int main() {
    int B[3];
    int n;
    for (int i = 0; i < 3; i++) {
        cin >> n;
        B[i] = n;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2 - i; j++) {
            if (B[i] > B[i+1]) {
            int temp = B[i];
            B[i] = B[i + 1];
            B[i + 1] = temp;
            }
        }
    }
    cout << B[0] + B[1];
    return 0;
}