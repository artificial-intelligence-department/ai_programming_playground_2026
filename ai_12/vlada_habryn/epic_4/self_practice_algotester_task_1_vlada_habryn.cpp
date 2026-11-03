
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int count = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] % 2 != a[i - 1] % 2) {
            count++;
        }
    }
    cout << count << endl;
    delete[] a;
    return 0;
}
