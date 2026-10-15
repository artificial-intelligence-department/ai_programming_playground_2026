#include <iostream>
using namespace std;

/*
 * Задача: Депутатські гроші
 * Щербак Орислав
 * Група ШІ-11
 */

int main() {
    long long n;
    cin >> n;
    int bills[] = {500, 200, 100, 50, 20, 10, 5, 2, 1};
    long long count = 0;
    // перебираємо номінали від найбільшого до найменшого
    for (int i = 0; i < 9; ++i) {
        count += n / bills[i];
        n %= bills[i];
    }
    cout << count << '\n';
    return 0;
}