#include <iostream>
using namespace std;

int gcd(int a, int b)
{
    while (b != 0){
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void mergeSort(int *a, int *temp, int left, int right)
{
    if (left >= right) return;

    int mid = left +(right - left)/2;
    mergeSort(a, temp, left, mid);
    mergeSort(a, temp, mid+1, right);

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right){
        if (a[i] <= a[j]){
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }

    while (i <= mid){
        temp[k++] = a[i++];
    }
    while (j <= right){
        temp[k++] = a[j++];
    }
    for (int i = left; i <= right; i++){
        a[i] = temp[i];
    }
}

int main()
{
    int n;
    cin >> n;

    int *a = new int[n];
    int *temp = new int[n];

    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    mergeSort(a, temp, 0, n-1);
    delete[] temp;

    int m = 1;
    for (int i = 1; i < n; i++){
        if (a[i] != a[m-1]){
            a[m] = a[i];
            m++;
        }
    }

    if (m == 1){
        cout << 2LL * a[0];
        delete[] a;
        return 0;
    }

    int *pref = new int[m];
    int *suff = new int[m];

    pref[0] = a[0];
    for (int i = 1; i < m; i++){
        pref[i] = gcd(pref[i-1], a[i]);
    }

    suff[m-1] = a[m-1];
    for (int i = m-2; i >= 0; i--){
        suff[i] = gcd(suff[i+1], a[i]);
    }

    long long answer = 0;
    for (int i = 0; i < m; i++){
        int other_gcd = 0;
        if (i > 0){
            other_gcd = gcd(other_gcd, pref[i-1]);
        }
        if (i < m-1){
            other_gcd = gcd(other_gcd, suff[i+1]);
        }

        long long current = (long long)a[i] + other_gcd;
        if (current > answer){
            answer = current;
        }
    }

    cout << answer;
    delete[] pref;
    delete[] suff;
    delete[] a;
    return 0;
}