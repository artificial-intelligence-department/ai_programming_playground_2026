#include <iostream>
#include <vector>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    long long k;
    if (!(cin >> n >> m >> k)) {
        return 0;
    }

    vector<long long> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
    }

    long long current_sum = 0;
    int workers_needed = 1; 

    for (int i = 0; i < m; ++i) {

        if (current_sum + a[i] > k) {
            workers_needed++;   
            current_sum = a[i];  
        } else {
            current_sum += a[i]; 
        }
    }

    if (workers_needed > n) {
        cout << -1 << "\n";
    } else {

        cout << n - workers_needed << "\n";
    }

    return 0;
}
