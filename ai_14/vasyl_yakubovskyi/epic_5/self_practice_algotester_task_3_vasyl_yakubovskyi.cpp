/*
Task: self_practice_algotester_task_3 (Марічка вмикає лампи)
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/

#include <iostream>
#include <iomanip>

using namespace std;

int main() {

    long long m, n;
    if (cin >> m >> n) {
        double ans = static_cast<double>(m + 1) / (m - n + 1);
        cout << fixed << setprecision(10) << ans << '\n';
    }

    return 0;
}