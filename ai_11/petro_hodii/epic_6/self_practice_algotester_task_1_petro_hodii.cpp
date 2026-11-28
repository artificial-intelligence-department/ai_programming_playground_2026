#include <iostream>
#include <cmath>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    long long first_x, first_y;
    long long prev_x, prev_y;
    
    cin >> first_x >> first_y;
    prev_x = first_x;
    prev_y = first_y;

    long long double_area = 0;
    long long boundary_points = 0;

    for (int i = 1; i < n; ++i) {
        long long curr_x, curr_y;
        cin >> curr_x >> curr_y;

        double_area += (prev_x * curr_y - curr_x * prev_y);

        boundary_points += gcd(abs(curr_x - prev_x), abs(curr_y - prev_y));

        prev_x = curr_x;
        prev_y = curr_y;
    }

    double_area += (prev_x * first_y - first_x * prev_y);
    boundary_points += gcd(abs(first_x - prev_x), abs(first_y - prev_y));

    double_area = abs(double_area);

    long long interior_points = (double_area - boundary_points + 2) / 2;

    cout << interior_points << "\n";

    return 0;
}