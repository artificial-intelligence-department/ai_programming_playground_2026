#include <iostream>
using namespace std;

int main() {
    int n;
    int k;
    cin >> n;
    cin >> k;

    for (int i = 1; i <= k; i++) {
        int d;
        cin >> d;

        while (n % d == 0) {
            n /= d;
        }
    }
    if (n==1){
        cout<<"YES"<<endl;
    }
    else {
        cout<<"NO"<<endl;
    }
}
