#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    long sum = 0;
    for (int i = n; i>0; i--) {
        long x;
        cin >>x;
        long k=x-1;
        sum+=k;
    }
    cout << sum;
    return 0;
}
