/*
Алготестер задача 1 Найбільша зростаюча підпослідовність
Станіслав Коваль
ШІ-12
*/


#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long a[100];
    int dp[100];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[i] = 1; 
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
    }

    int best = 0;
    for (int i = 0; i < n; i++) {
        if (best < dp[i]) {
            best = dp[i];
        }
    }

    cout << best << endl;
    return 0;
}
