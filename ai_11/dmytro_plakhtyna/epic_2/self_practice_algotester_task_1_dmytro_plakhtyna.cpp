#include <iostream>
using namespace std;

int main() {
    int n;
    int m;
    int k;
    cin >> n;
    cin >> m;
    cin >> k;
    if ((n * m) % k == 0) {
    cout << "Yes";
    } else {
        cout << "No";
    }
    cout << sizeof (long double) << endl;
    return 0;
} 
