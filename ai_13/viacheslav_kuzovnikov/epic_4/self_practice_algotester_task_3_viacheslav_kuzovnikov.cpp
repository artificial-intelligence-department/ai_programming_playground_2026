/*
Вправа
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
using namespace std;

int main() {
    long long n, k, m, p;
    cin >> n >> k >> m >> p;

    long long q = 0; 
    for (int i = 0; i < k; i++) {
        long long a;
        cin >> a;
        q += a;
    }

    long long rem = n - k;
    long long mod = q % p;

    
    long long need;
    if (mod == 0) {
        need = 0;
    } else {
        need = p - mod;
    }

    
    if (need <= rem * m) {
        cout << "Yes";
    } else {
        cout << "No";
    }

    return 0;
}