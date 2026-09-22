#include <iostream>
using namespace std;

int main() {
    int n;
     
    if (!(cin >> n) || n < 1 || n > 100000) {
        cout << "Помилка: n має бути цілим числом від 1 до 100000.\n";
        return 1;
    }

    long long total = 0;  

    for (int i = 0; i < n; i++) {
        long long a;
        if (!(cin >> a) || a < 0 || a > 1000000000) {
            cout << "Помилка: кількість печива в пачці має бути цілим числом від 0 до 1000000000.\n";
            return 1;
        }
        if (a > 0) {
            total += a - 1;
        }
    }

    cout << total << "\n";
    return 0;
}
