#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    vector<int> g;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        char event;
        cin >> event;

        if (event == '+') {
            int x;
            cin >> x;

            if (g.empty()) {
                g.push_back(x);
            }
            else {
                g.push_back(gcd(g.back(), x));
            }
        }
        else if (event == '-') {
            g.pop_back();
        }
        else if (event == '?') {
            cout << g.back() << '\n';
        }
    }

    return 0;
}