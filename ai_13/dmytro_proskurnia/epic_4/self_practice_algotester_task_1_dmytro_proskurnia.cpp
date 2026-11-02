//Проскурня Дмитро ШІ-13
//#1163 Гламурні ферзі

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(X) (X).begin(), (X).end()
using vi = vector<int>;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    vi arr(n); iota(all(arr), 0LL);
    int ans = 0;

    do {
        bool check = true;
        for (int i = 0; i < n; i++) {
            int k = 1;
            for (int j = i+1; j < n; j++) {
                if (arr[j] == arr[i]+k || arr[j] == arr[i]-k) {
                    check = false;
                    break;
                }
                k++;
            }
            if (!check) {
                break;
            }
        }
        if (check) {
            /*
            vvi board(n, vi(n, 0));
            for (int i = 0; i < n; i++) {
                board[i][arr[i]] = 1;
            }

            for (auto rows:board) {
                for (auto &el:rows) {
                    cout << el << " ";
                }
                cout << "\n";
            }
            cout << "\n\n";
            */
            ans++;
        }


    } while (next_permutation(all(arr)));
    cout << ans;

    return 0;
}

