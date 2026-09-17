#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long answer = 0;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        answer += a - 1;
    }

    cout << answer << endl;

    return 0;
}