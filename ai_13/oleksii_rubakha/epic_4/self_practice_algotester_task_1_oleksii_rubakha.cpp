
/* 
    Цікавий масив 
    Олексій Рубаха
    ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int a[100000];
    long long sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    if (sum % 2 != 0) {
        cout << "NI";
        return 0;
    }

    long long leftSum = 0;

    for (int i = 0; i < n - 1; i++) {
        leftSum += a[i];

        if (leftSum == sum / 2) {
            cout << "TAK";
            return 0;
        }
    }

    cout << "NI";

    return 0;
}