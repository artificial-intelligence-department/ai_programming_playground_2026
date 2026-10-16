#include <iostream>
using namespace std;

int cnt[3][10001];   // cnt[d][v] = скільки друзів хочуть рівно v грамів страви d

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int d = 0; d < 3; d++) {   // d=0 борщ, d=1 картопля, d=2 салат
            int x;
            cin >> x;
            cnt[d][x]++;
        }
    }

    long long total = 0;

    for (int d = 0; d < 3; d++) {
        // шукаємо медіану M
        int seen = 0, M = 0;
        for (int v = 0; v <= 10000; v++) {
            seen += cnt[d][v];
            if (seen > n / 2) {
                M = v;
                break;
            }
        }
        // рахуємо недовіру для цієї страви
        for (int v = 0; v <= 10000; v++) {
            int diff = v > M ? v - M : M - v;   // модуль різниці
            total += (long long)cnt[d][v] * diff;
        }
    }

    cout << total;
    return 0;
}


