#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int nominals[9] = {500, 200, 100, 50, 20, 10, 5, 2, 1};
    int total_banknotes = 0;

    for (int i = 0; i < 9; i++) {
        total_banknotes += n / nominals[i];
        
        n %= nominals[i];
    }

    cout << total_banknotes << endl;

    return 0;
}