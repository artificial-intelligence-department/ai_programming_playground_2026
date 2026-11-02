#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int k, n;
    cin >> k >> n;

    int* c = new int[n];        

    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    sort(c, c + n);              

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (k >= c[i]) {         
            k -= c[i];
            count++;
        } else {
            break;              
        }
    }

    cout << count << endl;

    delete[] c;                  
    c = nullptr;
    return 0;
}