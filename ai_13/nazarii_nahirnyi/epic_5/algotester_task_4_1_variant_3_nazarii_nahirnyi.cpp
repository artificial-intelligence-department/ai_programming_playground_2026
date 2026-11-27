#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int count;
    cin >> count;

    int rem0[1005], rem1[1005], rem2[1005];
    int cnt0 = 0, cnt1 = 0, cnt2 = 0;

    for (int i = 0; i < count; i++) {
        int num;
        cin >> num;

        if (num % 3 == 0) {
            rem0[cnt0] = num;
            cnt0++;
        } else if (num % 3 == 1) {
            rem1[cnt1] = num;
            cnt1++;
        } else {
            rem2[cnt2] = num;
            cnt2++;
        }
    }

    sort(rem0, rem0 + cnt0);
    sort(rem1, rem1 + cnt1);
    sort(rem2, rem2 + cnt2);

    cnt0 = unique(rem0, rem0 + cnt0) - rem0;
    cnt1 = unique(rem1, rem1 + cnt1) - rem1;
    cnt2 = unique(rem2, rem2 + cnt2) - rem2;

    cout << cnt0 + cnt1 + cnt2 << "\n";

    for (int i = 0; i < cnt0; i++) {
        cout << rem0[i] << " ";
    }
    for (int i = cnt1 - 1; i >= 0; i--) {
        cout << rem1[i] << " ";
    }
    for (int i = 0; i < cnt2; i++) {
        cout << rem2[i] << " ";
    }

    return 0;
}