#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    if (n > 7 || n < 1) {
        return 1;
    }

    bool grade90 = true;
    bool grade51 = true;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a > 100 || a < 0) {
            return 1;
        }

        if (a < 90)
            grade90 = false;

        if (a < 51)
            grade51 = false;
    }

    if (grade90) {
        cout << "Pidvyshchena";
    }
    else if (grade51) {
        cout << "Zvychaina";
    }
    else {
        cout << "Zabud pro stipendiiu";
    }
    return 0;
}