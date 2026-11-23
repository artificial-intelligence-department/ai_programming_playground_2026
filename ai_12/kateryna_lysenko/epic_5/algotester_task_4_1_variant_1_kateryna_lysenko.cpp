/*
Задача: Algotester Lab 4(1) 
Автор:   Катерирна Лисенко
Група:   ШІ-12
*/
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

void printSet(const vector<int> &v) {
    cout << v.size() << "\n";
    for (size_t i = 0; i < v.size(); i++) {
        if (i > 0) cout << " ";
        cout << v[i];
    }
    cout << "\n";
}

int main() {
    int n, m;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    cin >> m;
    vector<int> b(m);
    for (int &x : b) cin >> x;
    sort(a.begin(), a.end());       // алгоритми STL вимагають відсортованих діапазонів
    sort(b.begin(), b.end());

    vector<int> diffAB, diffBA, inter, uni, sym;
    set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(diffAB));
    set_difference(b.begin(), b.end(), a.begin(), a.end(), back_inserter(diffBA));
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(inter));
    set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(uni));
    set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(sym));

    printSet(diffAB); cout << "\n";
    printSet(diffBA); cout << "\n";
    printSet(inter);  cout << "\n";
    printSet(uni);    cout << "\n";
    printSet(sym);
    return 0;
}