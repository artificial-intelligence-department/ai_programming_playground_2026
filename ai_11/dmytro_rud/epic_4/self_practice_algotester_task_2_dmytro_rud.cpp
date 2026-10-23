#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> odd, even;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (x % 2 == 0) {
            even.push_back(x);
        } else {
            odd.push_back(x);
        }
    }

    if (abs((int)even.size() - (int)odd.size()) > 1) {
        cout << -1;
        return 0;
    }

    if (even.size() > odd.size()) {
        for (int i = 0; i < (int)odd.size(); i++) {
            cout << even[i] << ' ' << odd[i] << ' ';
        }
        cout << even.back();
    } else if (odd.size() > even.size()) {
        for (int i = 0; i < (int)even.size(); i++) {
            cout << odd[i] << ' ' << even[i] << ' ';
        }
        cout << odd.back();
    } else {
        for (int i = 0; i < (int)even.size(); i++) {
            cout << even[i] << ' ' << odd[i] << ' ';
        }
    }
}