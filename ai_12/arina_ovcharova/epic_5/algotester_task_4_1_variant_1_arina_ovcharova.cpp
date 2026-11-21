// Algotester Lab 4, варіант 1 - версія з STL
// різниці, перетин, об'єднання і симетрична різниця двох масивів
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

// сортую масив; повтори не прибираю - кожен елемент
// враховується стільки разів, скільки зустрічається (так приймає Algotester)
vector<int> makeSet(vector<int> v) {
    sort(v.begin(), v.end());
    return v;
}

void printSet(const vector<int> &s) {
    cout << s.size() << endl;
    for (size_t i = 0; i < s.size(); i++) {
        if (i > 0) cout << " ";
        cout << s[i];
    }
    cout << endl;
}

int main() {
    int n, m;
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

    // алгоритми set_... працюють тільки з посортованими даними
    a = makeSet(a);
    b = makeSet(b);

    vector<int> diffAB, diffBA, inter, uni, symDiff;

    set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(diffAB));
    set_difference(b.begin(), b.end(), a.begin(), a.end(), back_inserter(diffBA));
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(inter));
    set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(uni));
    set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(symDiff));

    printSet(diffAB);
    printSet(diffBA);
    printSet(inter);
    printSet(uni);
    printSet(symDiff);

    return 0;
}
