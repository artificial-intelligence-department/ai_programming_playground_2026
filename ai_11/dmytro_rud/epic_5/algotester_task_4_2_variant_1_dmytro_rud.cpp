#include <iostream>
#include <set>
#include <vector>

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

vector<int> diffe(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j])      res.push_back(a[i++]);
        else if (a[i] > b[j]) j++;
        else { i++; j++; }
    }
    while (i < a.size()) res.push_back(a[i++]);   // хвіст A
    return res;
}

vector<int> inters(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) i++;
        else if (a[i] > b[j]) j++;
        else {
            res.push_back(a[i]);
            i++;
            j++;
        }
    }
    return res;
}

vector<int> unions(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) res.push_back(a[i++]);
        else if (a[i] > b[j]) res.push_back(b[j++]);
        else {
            res.push_back(a[i]);
            i++;
            j++;
        }
    }
    while (i < a.size()) res.push_back(a[i++]);   // хвіст A
    while (j < b.size()) res.push_back(b[j++]);   // хвіст B
    return res;
}

vector<int> symDiff(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) res.push_back(a[i++]);
        else if (a[i] > b[j]) res.push_back(b[j++]);
        else {
            i++;
            j++;
        }
    }
    while (i < a.size()) res.push_back(a[i++]);   // хвіст A
    while (j < b.size()) res.push_back(b[j++]);   // хвіст B
    return res;
}

int main() {
    int n, m, x;
    multiset<int> sa, sb;
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> x; sa.insert(x); }
    cin >> m;
    for (int i = 0; i < m; i++) { cin >> x; sb.insert(x); }

    vector<int> a(sa.begin(), sa.end());
    vector<int> b(sb.begin(), sb.end());

    print(diffe(a, b));    cout << "\n";
    print(diffe(b, a));    cout << "\n";
    print(inters(a, b));   cout << "\n";
    print(unions(a, b));   cout << "\n";
    print(symDiff(a, b));
    return 0;
}