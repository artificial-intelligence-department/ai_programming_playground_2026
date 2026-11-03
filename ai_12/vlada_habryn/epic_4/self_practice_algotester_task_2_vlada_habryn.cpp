#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int* even = new int[n];
    int* odd = new int[n];
    int evenCount = 0;
    int oddCount = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x % 2 == 0) {
            even[evenCount] = x;
            evenCount++;
        } else {
            odd[oddCount] = x;
            oddCount++;
        }
    }
    if (evenCount > oddCount + 1 || oddCount > evenCount + 1) {
        cout << -1 << endl;
    } else {
        int e = 0, o = 0;
        bool takeEven = evenCount >= oddCount;
        for (int i = 0; i < n; i++) {
            if (takeEven) {
                cout << even[e];
                e++;
            } else {
                cout << odd[o];
                o++;
            }
            if (i < n - 1) {
                cout << " ";
            }
            takeEven = !takeEven;
        }
        cout << endl;
    }
    delete[] even;
    delete[] odd;
    return 0;
}
