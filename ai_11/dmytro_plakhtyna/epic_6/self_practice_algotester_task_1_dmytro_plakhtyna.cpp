//Яблука
#include <iostream>
using namespace std;

long long a[2001], c[2001], mn[2001];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long b;
    cin >> b;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        
    }
    for (int i = 0; i < n; i++) {
        mn[i] = c[i];

    }

    long long best = -1;
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            for (int j = 0; j < n; j++) {
                long long price = c[(j + i) % n];
                if (price < mn[j]) mn[j] = price;
            }
        }
        long long sum = i * b;
        for (int j = 0; j < n; j++) sum += a[j] * mn[j];
        if (best == -1 || sum < best) best = sum;
    }
    cout << best << endl;
}