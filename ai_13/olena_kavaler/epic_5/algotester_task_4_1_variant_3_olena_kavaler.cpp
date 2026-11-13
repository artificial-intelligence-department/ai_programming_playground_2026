
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(int a, int b) {
    int ra = a % 3;
    int rb = b % 3;

    if (ra != rb) {
        return ra < rb;
    }
    if (ra == 1) {
        return a > b;
    }
    return a < b;
}

int main() {
    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end(), cmp);

    v.erase(unique(v.begin(), v.end()), v.end());

    cout << v.size() << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

    return 0;
}