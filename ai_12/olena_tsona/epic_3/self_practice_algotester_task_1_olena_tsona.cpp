
#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

int main() {
    int r, n;
    cin >> n >> r;

    // pi * rsmall^2 = pi * r^2 / n, 
    double rsmall = r / sqrt((double)n);

    cout << fixed << setprecision(7) << rsmall << endl;

    return 0;
}