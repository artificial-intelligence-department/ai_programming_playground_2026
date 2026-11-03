//Марічка та печиво 0011
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int count [n];
    for (int i=0; i < n;i++) {
        cin >> count[i];
    }
    long long sum = 0;
    for (int i=0; i < n ;i++){
        sum+=count[i] - 1;
    }
    cout << sum;
}