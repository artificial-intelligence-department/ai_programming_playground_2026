#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int n,m,s;
    cin >> n >> m >> s;
    int sum = ceil((double)n / 2) * m;
    if (sum > s) {
        cout << -1 << endl;
        return 0;
    }
        
    int seq[n] = {0};
    int range = ceil((double)n / 2);
    for (int i = 0; i < range; i++) {
        seq[i] = m;
    }
    if (sum == s) {
        for (int i = 0; i < range; i++) {
            cout << m << " ";
        }
        for (int i = 0; i < (n - range); i++) {
            cout << 0 << " ";
        }
        cout << endl;
        return 0;
    }

    while (true) {
        if (sum < s) {
            seq[0]++;
            sum++;
        } else {
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << seq[i] << " ";
    }
    cout << endl;
    return 0;

}