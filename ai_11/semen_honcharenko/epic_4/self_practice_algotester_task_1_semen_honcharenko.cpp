/*
    Алготестер. "Elephant Coach"
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
using namespace std;

int main() {
    int n = 0;
    int max_x = 0;
    int min_x = 0;

    cin >> n;
    int coordinates[n] = {};
    for (int i = 0; i < n; i++) {
        cin >> coordinates[i];
        if (i == 0) {
            max_x = coordinates[i];
            min_x = coordinates[i];
        }
        if (coordinates[i] > max_x) {
            max_x = coordinates[i];
        }
        if (coordinates[i] < min_x) {
            min_x = coordinates[i];
        }
    }
    cout << max_x - min_x;
    return 0;
}