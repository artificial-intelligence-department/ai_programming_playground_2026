#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[100];
    for (int i = 0; i < n; i++) {  
        cin >> a[i];
    }
    int maxIdx = 0;                
    for (int i = 1; i < n; i++) {
        if (a[i] > a[maxIdx]) {     
            maxIdx = i;             
        }
    }
    cout << maxIdx;                
    return 0;
}
