#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    int a[131072]; // 2 в степені 17

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a, a + n); // сортуємо масив у порядку зростання, бо найменші числа треба віднімати, а найбільші додавати

    long long answer = 0;

    for (int i = 0; i < n / 2; i++) {
        answer -= a[i];          // найменші числа віднімаються
        answer += a[i + n / 2];  // найбільші числа додаються
    }

    cout << answer;
    return 0;
}