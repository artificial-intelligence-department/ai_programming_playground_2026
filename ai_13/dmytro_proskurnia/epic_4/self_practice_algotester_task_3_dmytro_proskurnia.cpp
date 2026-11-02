//Проскурня Дмитро ШІ-13
//#0215 Проблемний подарунок

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(X) (X).begin(), (X).end()
#define pb(X) push_back((X))
using vi = vector<int>;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string t; cin >> t;
    string numb; cin >> numb;
    if (t.size() > 4) {
        cout << "No solution.";
        return 0;
    }
    int n = stoi(t);
    string ans;
    for (int i = 0; i < (1 << (numb.size()-1)); i++) {
        int sum = numb[0] - '0';
        for (int j = 0; j < numb.size()-1; j++) {
            if ((i & (1 << j)) == 0) {
                sum += numb[j+1] - '0';
            } else {
                sum -= numb[j+1] - '0';
            }
        }
        if (sum == n) {
            string cand;
            cand.pb(numb[0]);
            for (int j = 0; j < numb.size()-1; j++) {
                if ((i & (1 << j)) == 0) {
                    cand.pb('+');
                } else {
                    cand.pb('-');
                }
                cand.pb(numb[j+1]);
            }
            if (ans.empty()) {
                ans = cand;
            } else {
                ans = min(ans, cand);
            }
        }
    }

    cout << (ans.empty() ? "No solution." : ans);

    return 0;
}

