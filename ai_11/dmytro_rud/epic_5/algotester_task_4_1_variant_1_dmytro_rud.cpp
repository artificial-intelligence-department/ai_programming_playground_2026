#include <iostream>
#include <set>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

void print(const vector<int>& res) {
    cout << res.size() << "\n";
    if (!res.empty()) {
        for (size_t i = 0; i < res.size(); i++) {
            if (i) cout << ' ';        
            cout << res[i];
        }
        cout << "\n";
    }
}

void diffe(const multiset<int>& a, const multiset<int>& b) {
    vector<int> res;
    set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));
    print(res);
}

void inters(const multiset<int>& a, const multiset<int>& b) {
    vector<int> res;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));
    print(res);
}

void unions(const multiset<int>& a, const multiset<int>& b) {
    vector<int> res;
    set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));
    print(res);
}

void symmetric_diffe(const multiset<int>& a, const multiset<int>& b) {
    vector<int> res;
    set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));
    print(res);
}

int main() {
    int n, m, x;
    multiset<int> a, b;                 // multiset: дублікати зберігаються

    cin >> n;
    for (int i = 0; i < n; i++) { cin >> x; a.insert(x); }
    cin >> m;
    for (int i = 0; i < m; i++) { cin >> x; b.insert(x); }

    diffe(a, b);           cout << "\n";
    diffe(b, a);           cout << "\n";
    inters(a, b);          cout << "\n";
    unions(a, b);          cout << "\n";
    symmetric_diffe(a, b); 

    return 0;
}