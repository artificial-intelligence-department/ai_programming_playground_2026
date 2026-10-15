/* Факторіал
    1153    */
#include <iostream>
using namespace std;

long long countZeros(long long N) {
    long long count = 0;

    while (N / 5 > 0) {
        count += N / 5;
        N /= 5;
    }

    return count;
}

int main() {
    long long N;
    cin >> N;

    cout << countZeros(N) << endl;

    return 0;
}
