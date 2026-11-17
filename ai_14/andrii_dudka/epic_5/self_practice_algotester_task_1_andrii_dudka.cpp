#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long current = 0;
    long long smallest = 0;
    long long largest = 0;

    for (int i = 1; i < n; ++i) {
        long long a;
        cin >> a;
        current += a;

        if (current < smallest) {
            smallest = current;
        }
        if (current > largest) {
            largest = current;
        }
    }

    long long nearest = -smallest;
    if (largest < nearest) {
        nearest = largest;
    }

    cout << largest - smallest + nearest << '\n';
}