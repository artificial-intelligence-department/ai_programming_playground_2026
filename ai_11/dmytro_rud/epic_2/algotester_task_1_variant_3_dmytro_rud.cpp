#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long a1,a2,a3,a4,a5;

    cin >> a1;
    cin >> a2;
    cin >> a3;
    cin >> a4;
    cin >> a5;

    vector<long long> aj = {a1, a2, a3, a4, a5};
    for (int i = 0; i < 4; i++) {
        if (aj[i] < 1 or aj[i+1] < 1) {
            cout << "ERROR";
            return 0; 
        }
        if (aj[i] < aj[i + 1]) {
            cout << "LOSS";
            return 0;
        }
    }
    cout << "WIN";
    return 0;
}