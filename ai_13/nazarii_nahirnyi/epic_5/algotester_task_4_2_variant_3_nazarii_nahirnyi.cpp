#include <iostream>

using namespace std;

void qs(int a[], int l, int r) {
    int i = l, j = r;
    int p = a[(l + r) / 2];
    while (i <= j) {
        while (a[i] < p) i++;
        while (a[j] > p) j--;
        if (i <= j) {
            int t = a[i];
            a[i++] = a[j];
            a[j--] = t;
        }
    }
    if (l < j) qs(a, l, j);
    if (i < r) qs(a, i, r);
}

int removeDuplicates(int a[], int n) {
    if (n == 0) {
        return 0;
    }
    int k = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i - 1]) {
            a[k] = a[i];
            k++;
        }
    }
    return k;
}

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

    if (cnt0 > 0) {
        qs(rem0, 0, cnt0 - 1);
    }
    if (cnt1 > 0) {
        qs(rem1, 0, cnt1 - 1);
    }
    if (cnt2 > 0) {
        qs(rem2, 0, cnt2 - 1);
    }

    cnt0 = removeDuplicates(rem0, cnt0);
    cnt1 = removeDuplicates(rem1, cnt1);
    cnt2 = removeDuplicates(rem2, cnt2);

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