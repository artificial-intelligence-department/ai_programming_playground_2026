#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    int* a = new int[n];         

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a, a + n);              
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0 && (i == 0 || a[i] != a[i - 1])) {
            count++;             
        }
    }

    cout << count << endl;

    delete[] a;                  
    a = nullptr;
    return 0;
}


