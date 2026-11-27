// З STL
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

vector<int> read_and_sort_vector() {
    int size;
    cin >> size;

    vector<int> v(size);
    for (int& x : v) cin >> x;

    sort(v.begin(), v.end());
    return v;
}

vector<int> get_res(const vector<int> &a, const vector<int> &b, int operation) {
    vector<int> res;
    auto out = back_inserter(res);

    switch (operation) {
        case 1: set_difference(a.begin(), a.end(), b.begin(), b.end(), out); break;
        case 2: set_difference(b.begin(), b.end(), a.begin(), a.end(), out); break;
        case 3: set_intersection(a.begin(), a.end(), b.begin(), b.end(), out); break;
        case 4: set_union(a.begin(), a.end(), b.begin(), b.end(), out); break;
        case 5: set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), out); break;
    }
    return res;
}

void print_res(const vector<int>& v) {
    cout << v.size() << '\n';

    for (size_t i {0}; i < v.size(); i++) {
        if (i > 0) cout << ' ';
        cout << v[i];
    }
    cout << '\n';
}

int main() {
    int n, m;

    vector<int> a = read_and_sort_vector();
    vector<int> b = read_and_sort_vector();

    for (int op {1}; op <= 5; op++) {
        print_res(get_res(a, b, op));
        if (op < 5) cout << '\n';
    }

}