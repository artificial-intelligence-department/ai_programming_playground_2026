#include <iostream>
using namespace std;


int main() {
    int n;
    cin >> n;
    long long cookies = 0;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        if (a>0){
            cookies += (a-1);
        }
    }
    cout << cookies << endl;
    return 0;
}