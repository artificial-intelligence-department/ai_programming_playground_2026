/* 
Умова: https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/40395
Автор: Давидович Святослав
Група: ШІ-11
*/

#include <iostream>

using namespace std;

const long long MOD = 1000000007;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    if (base < 0) base += MOD;
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (__int128)res * base % MOD;
        }
        base = (__int128)base * base % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long x, d, q, n;
    cin >> x >> d >> q >> n;

    x %= MOD;
    d %= MOD;
    q %= MOD;

    long long ans = 0;

    if (q == 1) {
        long long term1 = (__int128)x * ((n + 1) % MOD) % MOD;
        
        // n * (n + 1) / 2
        long long n_mod = n % MOD;
        long long n_plus_1_mod = (n + 1) % MOD;
        long long sum_i = (__int128)n_mod * n_plus_1_mod % MOD;
        sum_i = (__int128)sum_i * modInverse(2) % MOD;
        
        long long term2 = (__int128)d * sum_i % MOD;
        
        ans = (term1 + term2) % MOD;
    } else {
        long long p1 = power(q, (n + 1) % (MOD - 1));
        long long p2 = (__int128)p1*q % MOD;

        // x * (q^(n+1) - 1) / (q - 1)
        long long num1 = (p1 - 1 + MOD) % MOD;
        long long den1_inv = modInverse(q - 1);
        long long term1 = (__int128)x * num1 % MOD;
        term1 = (__int128)term1 * den1_inv % MOD;

        // d * (n * q^(n+2) - (n+1) * q^(n+1) + q) / (q - 1)^2
        long long n_mod = n % MOD;
        long long n_plus_1_mod = (n + 1) % MOD;

        long long part_a = (__int128)n_mod * p2 % MOD;
        long long part_b = (__int128)n_plus_1_mod * p1 % MOD;
        
        long long num2 = (part_a - part_b + q + MOD) % MOD;
        
        long long den2 = (__int128)(q - 1) * (q - 1) % MOD;
        long long den2_inv = modInverse(den2);

        long long term2 = (__int128)d * num2 % MOD;
        term2 = (__int128)term2 * den2_inv % MOD;

        ans = (term1 + term2) % MOD;
    }

    if (ans < 0) ans += MOD;
    cout << ans;

    return 0;
}