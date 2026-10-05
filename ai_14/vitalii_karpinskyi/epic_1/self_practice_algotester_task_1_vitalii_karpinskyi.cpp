/*
Задача: Марічка і печиво (алготестер)
Карпінський Віталій
СШІ-14
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    long long total = 0;
    for (int i = 1; i <= n; i = i + 1) {
        long long a;
        cin >> a;
        total = total + (a-1);
    }
    cout << total << endl;

    return 0;
}