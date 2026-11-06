/* №1401 Хробуст Андрій ШІ-11

*/
#include <iostream>
using namespace std;

void crosings(const int* a, int n, int& count) {
    count = 0;
    for (int i = 1; i < n; i++) {
        int dif = *(a + i) - *(a + i - 1);
        if (abs(dif) % 2 == 1) {
            count++;
        }
    }
}

int main() {
    int n;
    int a[100000];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> *(a + i);
    }
    int count = 0;
    crosings(a, n, count);
    cout << count;
    return 0;
}