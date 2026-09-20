#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int pechivo = 0;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a > 0) {
            pechivo += (a - 1);
        }
    }

    cout << pechivo << endl;

    return 0;
}