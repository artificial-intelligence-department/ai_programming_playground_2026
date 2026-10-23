#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    int days[n];
    for (int i = 0; i < n; i++) {
        cin >> days[i];
    }
    for(int i = 0; i < n; i++) {
        if (days[i] > 0) {
            cout << 1+i << " ";
        } else {continue;}
    }
}
