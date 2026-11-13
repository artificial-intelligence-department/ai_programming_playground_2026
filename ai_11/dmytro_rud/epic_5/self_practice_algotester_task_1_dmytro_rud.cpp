#include <iostream>
#include <algorithm>

using namespace std;

long long has_number(long long x, long long L, long long R) {
    if (L <= x && x <= R) {
        return 1;
    }
    return 0;
}

long long count_ge5(long long L, long long R) {
    long long start = max(L, 5LL);
    if (start > R) {
        return 0;
    }
    return R - start + 1;
}

long long count_pairs_less(long long L1, long long R1, long long L2, long long R2) {
    if (L1 > R1 || L2 > R2) {
        return 0;
    }

    long long pairs = 0;

    long long right_limit = min(R1, L2 - 1);
    if (L1 <= right_limit) {
        long long count_x = right_limit - L1 + 1;
        long long count_y = R2 - L2 + 1;
        pairs = pairs + count_x * count_y;
    }

    long long ov_L = max(L1, L2);
    long long ov_R = min(R1, R2);

    if (ov_L <= ov_R) {
        long long n = ov_R - ov_L + 1;
        long long first = R2 - ov_L;
        long long last = R2 - ov_R;

        pairs = pairs + n * (first + last) / 2;
    }

    return pairs;
}

int main() {
    long long j1, j2, b1, b2;
    cin >> j1 >> j2 >> b1 >> b2;

    long long j_has_1 = has_number(1, j1, j2);
    long long j_has_2 = has_number(2, j1, j2);
    long long j_has_3 = has_number(3, j1, j2);
    long long j_has_4 = has_number(4, j1, j2);
    long long j_big   = count_ge5(j1, j2);

    long long b_has_1 = has_number(1, b1, b2);
    long long b_has_2 = has_number(2, b1, b2);
    long long b_has_3 = has_number(3, b1, b2);
    long long b_has_4 = has_number(4, b1, b2);
    long long b_big   = count_ge5(b1, b2);

    long long win_j = 0;
    win_j += b_has_1 * (j_has_2 + j_has_3 + j_has_4 + j_big);
    win_j += j_has_2 * b_big;
    win_j += j_has_3 * (b_has_2 + b_has_4 + b_big);
    win_j += j_has_4 * b_big;
    win_j += count_pairs_less(max(j1, 5LL), j2, max(b1, 5LL), b2);

    long long win_b = 0;
    win_b += j_has_1 * (b_has_2 + b_has_3 + b_has_4 + b_big);
    win_b += b_has_2 * j_big;
    win_b += b_has_3 * (j_has_2 + j_has_4 + j_big);
    win_b += b_has_4 * j_big;
    win_b += count_pairs_less(max(b1, 5LL), b2, max(j1, 5LL), j2);

    long long total = win_j + win_b;

    if (total == 0) {
        cout << "0/1 0/1" << endl;
        return 0;
    }

    long long gcd_j = __gcd(win_j, total);
    long long gcd_b = __gcd(win_b, total);

    cout << (win_j / gcd_j) << "/" << (total / gcd_j) << " ";
    cout << (win_b / gcd_b) << "/" << (total / gcd_b) << endl;

    return 0;
}
