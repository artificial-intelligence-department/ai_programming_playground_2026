#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int n=1;
    double sum = 0;
    double m = 2;
    while (m >= 0.00001) {
        sum +=m;
        n++;
        m = m * 2 * pow((n - 1.0) / n, n - 1);
    }
    cout << "Sum: " << sum << endl;
    return 0;
}
