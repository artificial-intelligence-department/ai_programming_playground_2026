#include <iostream>
using namespace std;

int main() {
    long long n, k;
    cin >> n >> k;

    long long cur = 0;   // довжина поточної серії загострених зубів
    long long best = 0;  // найдовша серія

    for (long long i = 0; i < n; i++) {
        long long a;
        cin >> a;
        if (a >= k) {
            cur++;                   // зуб загострений: серія продовжується.
            if (cur > best) best = cur;
        } else {
            cur = 0;                 // зуб не загострений: серія обривається
        }
    }

    cout << best << endl;
    return 0;
}