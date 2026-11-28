
#include <iostream>
#include <iomanip>

using namespace std;

double get_max_abs_sum(int n, const double a[], double x) {
    double cur_max = 0.0, cur_min = 0.0, ans = 0.0;

    for (int i = 0; i < n; ++i) {
        double val = a[i] - x;

        cur_max = (cur_max + val > 0.0) ? (cur_max + val) : 0.0;
        cur_min = (cur_min + val < 0.0) ? (cur_min + val) : 0.0;

        if (cur_max > ans) ans = cur_max;
        if (-cur_min > ans) ans = -cur_min;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    static double a[100005];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    double l = -1000000.0, r = 1000000.0;
    for (int iter = 0; iter < 100; ++iter) {
        double m1 = l + (r - l) / 3.0;
        double m2 = r - (r - l) / 3.0;

        if (get_max_abs_sum(n, a, m1) < get_max_abs_sum(n, a, m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }

    cout << fixed << setprecision(6) << get_max_abs_sum(n, a, l) << "\n";
    return 0;
}