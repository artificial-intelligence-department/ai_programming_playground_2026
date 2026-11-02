#include <iostream>

using namespace std;

int main() {


    int n;
    cin >> n;

    int* r = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> r[i];
    }

    int a, b, c;
    cin >> a >> b >> c;

    // Прапорці для відстеження, чи було вже видалено відповідне число
    bool delA = false, delB = false, delC = false;

    // Масив для збереження елементів після видалення
    int* filtered = new int[n];
    int nNew = 0;

    for (int i = 0; i < n; ++i) {
        if (!delA && r[i] == a) {
            delA = true;
        } else if (!delB && r[i] == b) {
            delB = true;
        } else if (!delC && r[i] == c) {
            delC = true; 
        } else {
            filtered[nNew++] = r[i]; 
        }
    }
    int m = 0;
    if (nNew >= 2) {
        m = nNew - 1;
    }
    else{
        m = 0;
    }

    cout << m << "\n";

    if (m > 0) {
        for (int i = 0; i < m; ++i) {
            cout << (filtered[i] + filtered[i + 1]) << " ";
        }
        cout << "\n";
    }


    delete[] r;
    delete[] filtered;

    return 0;
}