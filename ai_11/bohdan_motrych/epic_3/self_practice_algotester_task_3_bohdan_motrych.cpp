#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    if (!(cin >> n)) {
        return 0;
    }

    long long max_value;
    for (int i = 0; i < n; i++) {
        long long value;
        cin >> value;
        
        if (i == 0 || value > max_value) {
            max_value = value;
        }
    }

    cout << max_value << endl;

    return 0;
}