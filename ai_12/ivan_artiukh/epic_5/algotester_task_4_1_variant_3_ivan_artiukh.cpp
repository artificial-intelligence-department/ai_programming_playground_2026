#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_arr(const vector<int>& a) {
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) cout << " ";
        cout << a[i];
    }
    cout << "\n";
}

int main() {
    int n = 0;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    auto it1 = partition(a.begin(), a.end(), [](int x) { return x % 3 == 0; });
    auto it2 = partition(it1, a.end(), [](int x) { return x % 3 == 1; });

    sort(a.begin(), it1);            
    sort(it1, it2, greater<int>());     
    sort(it2, a.end());             
    a.erase(unique(a.begin(), a.end()), a.end());

    cout << a.size() << "\n";
    print_arr(a);

    return 0;
}