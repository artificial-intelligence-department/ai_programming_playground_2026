//З використанням STL

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

void print(const vector<int>& v){
    cout << v.size() << "\n";
    for (size_t i = 0; i < v.size(); i++){
        if (i) cout << " ";
        cout << v[i];
    }
    cout << "\n";
}

vector<int> read(){
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());       
    return v;
}

int main(){
    vector<int> a = read();
    vector<int> b = read();
    vector<int> r;

    set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(r));
    print(r);
    r.clear();

    set_difference(b.begin(), b.end(), a.begin(), a.end(), back_inserter(r));
    print(r);
    r.clear();

    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(r));
    print(r);
    r.clear();

    set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(r));
    print(r);
    r.clear();

    set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(r));
    print(r);

    return 0;
}
