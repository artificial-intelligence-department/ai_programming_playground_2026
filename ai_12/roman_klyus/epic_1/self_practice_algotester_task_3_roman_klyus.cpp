#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int a, b, c, r;
    cin >> a >> b >> c >> r;

    double p = (a + b + c) / 2.0;
    double S = pow(p*(p - a)*(p - b)*(p - c), 0.5);
    double r1 = S / p;
    double R1 = (a * b * c) / (4 * S);

    if (R1 <= r) cout << '+';
    else cout << '-';

    if (r1 >= r) cout << "+";
    else cout << '-' << endl;


    return 0;
}
