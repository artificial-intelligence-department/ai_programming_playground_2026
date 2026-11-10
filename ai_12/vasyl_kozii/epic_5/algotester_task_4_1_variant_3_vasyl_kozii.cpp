/*
Algotester Task 4 1 Variant 3
Козій Василь Іванович
група: ШІ-12
*/
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    if (!(cin >> N)) return 0;
    int a[1005];
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }
    int* it1 = partition(a, a + N, [](int x) {
        return x % 3 == 0;
    });
    int* it2 = partition(it1, a + N, [](int x) {
        return x % 3 == 1;
    });
    sort(a, it1);
    sort(it1, it2, greater<int>());
    sort(it2, a + N);
    int* u1 = unique(a, it1);
    int* u2 = unique(it1, it2);
    int* u3 = unique(it2, a + N);
    int res[1005];
    int M = 0;
    for (int* p = a; p < u1; ++p) res[M++] = *p;
    for (int* p = it1; p < u2; ++p) res[M++] = *p;
    for (int* p = it2; p < u3; ++p) res[M++] = *p;
    cout << M << "\n";
    for (int i = 0; i < M; ++i) {
        cout << res[i] << (i + 1 == M ? "" : " ");
    }
    cout << "\n";
}