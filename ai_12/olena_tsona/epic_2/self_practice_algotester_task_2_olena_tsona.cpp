#include <iostream>

using namespace std;

int main() {
   
    int n;
    cin >> n;

    long long x;
    cin >> x;

    long long xmin = x;
    long long xmax = x;

    for (int i = 1; i < n; ++i) {
        cin >> x;
        if (x < xmin) {
            xmin = x;
        }
        if (x > xmax) {
            xmax = x;
        }
    }

    cout << xmax - xmin << endl;

    return 0;
}