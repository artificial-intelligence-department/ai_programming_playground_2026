#include <iostream>

using namespace std;

int main() {
    long long h[4];
    long long d[4];

    for(int i = 0; i < 4; i++) {
        cin >> h[i];
    }

    for(int i = 0; i < 4; i++) {
        cin >> d[i];
    }

    for(int i = 0; i < 4; i++) {
        if (d[i] > h[i]) {
            cout << "ERROR";
            return 0;
        }
    }

    bool isFallen = false;

    for(int i = 0; i < 4; i++) {
        h[i] = h[i] - d[i];

        long long maxH = h[0];
        long long minH = h[0];
        for(int j = 1; j < 4; j++) {
            if(h[j] > maxH) maxH = h[j];
            if(h[j] < minH) minH = h[j];
        }

        if(maxH >= minH * 2) {
            isFallen = true;
        }
    }

    bool equalH = true;
    for(int i = 1; i < 4; i++) {
        if(h[0] != h[i]) {
            equalH = false;
        }
    }

    if(equalH == true && isFallen == false && h[0] > 0) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }

    return 0;
}