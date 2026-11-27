/*1. Різницю N-M
2. Різницю M-N
3. Їх перетин
4. Їх обєднання
5. Їх симетричну різницю*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

void printSet(vector<int> v) {
    cout << v.size() << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main() {
    int n, m;

    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; i++) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int> riz1, riz2, peretyn, ob, symriz;

    set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(riz1));
    set_difference(b.begin(), b.end(), a.begin(), a.end(), back_inserter(riz2));
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(peretyn));
    set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(ob));
    set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(symriz));

    printSet(riz1);
    printSet(riz2);
    printSet(peretyn);
    printSet(ob);
    printSet(symriz);

    return 0;
}

