/*
Marichka and cookies
Мішин ШІ-14
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    if (0>n||n>100000){
       return 1;
    }
    int a[n];
    long int sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i=0; i<n; i++){
        if (0>a[i]||a[i]>1000000000){
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            sum = sum + a[i] - 1;
        }
    }
    cout << sum;

    return 0;
}