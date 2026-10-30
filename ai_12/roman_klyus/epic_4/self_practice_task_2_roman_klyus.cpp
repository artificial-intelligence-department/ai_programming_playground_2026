#include <iostream>

using namespace std;

long long find_gcd(long long a, long long b) {
    if (b == 0) return a;
    return find_gcd(b, a % b);
}

long long find_arr_gcd(long long arr[], int n) {
    if (n == 1) return arr[0];
    return find_gcd(arr[n-1], find_arr_gcd(arr, n - 1));
}

int main() {
    int n;
    cin >> n;
    long long arr[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    long long res_gcd = find_arr_gcd(arr, n);
    long long res = 0;

    for (int i = 0; i < n; i++) {
        res += arr[i] / res_gcd;
    }

    cout << res << endl;

}