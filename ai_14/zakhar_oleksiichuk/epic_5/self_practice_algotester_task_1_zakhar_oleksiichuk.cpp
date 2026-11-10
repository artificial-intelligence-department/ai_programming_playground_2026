#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long n;
    cin >> n;

    long long M = 1;
    while (M * (M + 1) / 2 < n) M++; 

    for (long long m = M; m < M + 100; m++) {
        long long d = m * (m + 1) / 2 - n;          
        for (long long L = 1; L <= m; L++) {
            long long d2 = d - L * (L - 1) / 2;    
            if (d2 < 0) break;
            if (2 * d2 > m - L) continue;   

            vector<int> a;
            for (int i = 0; i < L; i++) a.push_back(1);
            int color = 2;
            for (int i = 0; i < d2; i++) {
                a.push_back(color++);     
                a.push_back(1);         
            }
            while ((long long)a.size() < m) a.push_back(color++);

            cout << a.size() << "\n";
            for (int x : a) cout << x << " ";
            return 0;
        }
    }
}