/*
Обробка масиву, Момоток Артем, ШІ-13
*/
#include <iostream>

using namespace std;

bool seen[1000001];

int main() {
    int n;
    cin >> n;

    int count = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x > 0 && !seen[x]) {
            seen[x] = true;
            count++;
        }
    }
    
    cout << count << "\n";
    return 0;
}