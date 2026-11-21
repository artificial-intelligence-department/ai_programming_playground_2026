#include <iostream>

using namespace std;

int main() {

    int n;
    long long m;
    if (!(cin >> n >> m)) return 0;

    long long sum_sq = 0;
    for (int i = 0; i < n; ++i) {
        long long a;
        cin >> a;
       
        long long r = (a % m + m) % m; //  взяття за модулем для від'ємних та додатних чисел

        long long sq = (r * r) % m; // Обчислення квадрата залишку

        sum_sq = (sum_sq + sq) % m;     // Додавання до загальної суми за модулем m.
    }
    if (sum_sq == 0) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return 0;
}