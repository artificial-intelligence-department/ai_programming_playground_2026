#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    int sum = 0;
    for (int i = n; i>0; i--) {
        int x;
        cin >>x;
        int k=x-1;
        sum+=k;
    }
    cout << sum;
    return 0;
}