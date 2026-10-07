#include <iostream>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;

    // Від 9:00 ранку до 21:00 вечора є 13 прийомів чаю.
    const long long terms = 13;
    const long long intervals = terms - 1;

    // Різниця прогресії має бути цілим числом.
    if ((b - a) % intervals != 0) {
        cout << -1 << endl;
        return 0;
    }


    cout << terms * (a + b) / 2 << endl;

    return 0;
}