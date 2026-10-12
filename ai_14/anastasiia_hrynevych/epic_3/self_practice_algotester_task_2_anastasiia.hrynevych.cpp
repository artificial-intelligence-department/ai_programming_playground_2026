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
    int ieven = 0, iodd = 0;
    bool whichturn = even > odd;
    if (even == odd) whichturn = a[0] % 2 == 0;
    if (abs(even - odd) <= 1) {
        for (int i = 0; i < n; i++) {
            if (whichturn == true) {
                cout << evens[ieven] << " ";
                ieven++;
            } 
            else if (whichturn == false) {
                cout << odds[iodd] << " ";
                iodd++;
            }
            whichturn = !whichturn;
        }
        
    } 
    else cout << "-1" << "\n";
}