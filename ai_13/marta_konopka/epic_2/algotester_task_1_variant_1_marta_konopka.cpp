#include <iostream>
using namespace std;

int main() {
   
    long long H, M;
    cin >> H >> M;

  
    long long h[3];
    long long m[3];

 
    for (int i = 0; i < 3; i++) {
        cin >> h[i] >> m[i];
    }


    for (int i = 0; i < 3; i++) {
        if (h[i] > 0 && m[i] > 0) {
            cout << "NO" << endl;
            return 0; 
        }
    }


    for (int i = 0; i < 3; i++) {
        H = H - h[i];
        M = M - m[i];
    }


    if (H > 0 && M > 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}