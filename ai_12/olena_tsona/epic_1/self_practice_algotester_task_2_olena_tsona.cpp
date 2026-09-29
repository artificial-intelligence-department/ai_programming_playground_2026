#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n; 

    long long resCookies = 0; 

    for (int i = 0; i < n; i++) {
        long long cookies;
        cin >> cookies; 

        if (cookies > 0) {
            resCookies = resCookies + (cookies - 1);
        }
    }

    cout << resCookies << endl; 

    return 0;
}