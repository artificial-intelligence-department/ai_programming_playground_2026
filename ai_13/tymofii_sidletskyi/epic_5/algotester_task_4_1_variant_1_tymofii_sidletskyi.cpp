#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace::std;
/* Алготестер лаб 4.1 варіант 1
   Сідлецький Тимофій ШІ-13*/
int main () {
    int n,m;
    vector<int> result;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sort (a.begin(), a.end());
    sort (b.begin(), b.end());

    set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
    cout << result.size() << endl;
    for (int x : result) {
        cout << x << " ";
    }
    result.clear();
    cout << endl;

    set_difference(b.begin(), b.end(), a.begin(), a.end(), back_inserter(result));
    cout << result.size() << endl;
    for (int x : result) {
        cout << x << " ";
    }
    result.clear();
    cout << endl;

    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
    cout << result.size() << endl;
    for (int x : result) {
        cout << x << " ";
    }
    result.clear();
    cout << endl;
    set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
    cout << result.size() << endl;
    for (int x : result) {
        cout << x << " ";
    }
    result.clear();
    cout << endl;
    set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
    cout << result.size() << endl;
    for (int x : result) {
        cout << x << " ";
    }
    result.clear();
    cout << endl;
    

    return 0;
}