#include <iostream>
using namespace std;
int main(){
    int n, k;
    cin >> n;
    cin >> k;
    if (n>k*3 or n<k) {
        cout << "Impossible";
    } else {
        int min = n/k;
        int rest = n%k;
        for (int i = 0; i<k; i++) {
            if (rest>0) {
                cout << min+1 << " ";
                rest--;

            } else {
                cout << min << " ";
            }
        }
    }
    return 0;
}
