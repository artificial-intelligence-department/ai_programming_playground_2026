//цікаве листування
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main() {
    int k;
    string str;
    char a[1000][1000];
    cin >> k;
    int size = sqrt(k);
    cin >> str;
    int pos = 0;
    for (int i = 0; i < size; i++) {
        for (int q = 0; q < size; q++) {
            a[i][q] = str[pos];
            pos++;
        }
    }
    for (int sum = 0; sum < 2 * size - 1; sum++) {
        for (int i = 0; i < size; i++) {
            int q = sum - i;

            if (q >= 0 && q < size) {
                cout << a[i][q];
            }
        }
    }
    return 0;
}