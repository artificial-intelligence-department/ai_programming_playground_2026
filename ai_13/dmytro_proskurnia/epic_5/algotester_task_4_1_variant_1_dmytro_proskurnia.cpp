#include <bits/stdc++.h>
using namespace std;

#define all(X) (X).begin(), (X).end()
#define pb(X) push_back((X))
using vi = vector<int>;

int main() {

    int n; cin >> n;
    vi A(n); for (auto& el : A) cin >> el;

    int m; cin >> m;
    vi B(m); for (auto& el : B) cin >> el;
    sort(all(A)); sort(all(B));

    vector<int> diffAB, diffBA, inter, uni, symm;

    set_difference(all(A), all(B), back_inserter(diffAB));
    set_difference(all(B), all(A), back_inserter(diffBA));
    set_intersection(all(A), all(B), back_inserter(inter));
    set_union(all(A), all(B), back_inserter(uni));
    set_symmetric_difference(all(A), all(B), back_inserter(symm));

    for (auto& arr : {diffAB, diffBA, inter, uni, symm}) {
        cout << arr.size() << "\n";
        for (int x : arr) cout << x << " ";
        cout << "\n\n";
    }
    return 0;
}