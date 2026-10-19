#include <iostream>
using namespace std; 
int main() {
    int a;
    cin >> a;
    int count[a];
    for (int i = 0; i < a; ++i) {
        cin >> count[i];
    }

    int minVal, maxVal;
    minVal = count[0];
    maxVal = count[0];
    for (int i = 1; i < a; ++i) {
        if (count[i] < minVal) minVal = count[i];
        if (count[i] > maxVal) maxVal = count[i];
    }
    
    cout << maxVal - minVal;
    return 0;
}