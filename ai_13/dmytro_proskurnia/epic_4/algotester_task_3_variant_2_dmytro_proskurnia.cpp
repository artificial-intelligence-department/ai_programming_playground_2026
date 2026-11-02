//Проскурня Дмитро ШІ-13

#include <bits/stdc++.h>
using namespace std;
#define int long long

constexpr int MAX = 2e9+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    int arr1[n]; for (auto& el:arr1) cin >> el;
    int m; cin >> m;
    int arr2[m]; for (auto& el:arr2) cin >> el;

    int un = 0;
    for (auto el1:arr1) {
        for (auto el2:arr2) {
            if (el1 == el2) {
                un++;
                break;
            }
        }
    }

    int inter = n+m;
    for (auto el1:arr1) {
        for (auto el2:arr2) {
            if (el1 == el2) {
                inter--;
                break;
            }
        }
    }

    cout << un << "\n" << inter;

    return 0;
}

