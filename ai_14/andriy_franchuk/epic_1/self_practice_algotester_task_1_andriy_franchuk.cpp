#include <iostream>
using namespace std;

int main() {
    long long H, M;
    cin >> H >> M;
    if((H < 1 || M < 1)||(H > 1000000000000 || M > 1000000000000)){
        cout << "Error\n";
        return 0;
    }

    long long h[3], m[3];

    for (int i = 0; i < 3; i++) {
        cin >> h[i] >> m[i];
        if((h[i] < 0 || m[i] < 0)||(h[i] > 1000000000000 || m[i] > 1000000000000)){
            cout << "Error\n";
            return 0;
    }
}

    long long currentM = M;
    long long currentH = H;

    for (int i = 0; i < 3; i++) {
            currentM -= m[i];
            currentH -= h[i];
        }
    for (int i = 0; i < 3; i++) {
        if (!(h[i] == 0) && !(m[i] == 0)) {
            cout << "NO\n";
            return 0;
        }
    }
    if (currentH > 0 && currentM > 0) {
        cout << "YES\n";
        return 0;
    }

    cout << "NO\n";

    return 0;
}