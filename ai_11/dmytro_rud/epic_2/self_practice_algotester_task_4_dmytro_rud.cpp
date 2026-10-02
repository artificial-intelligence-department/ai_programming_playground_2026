#include <iostream>

using namespace std;

int main() {
    long long low = 1;
    long long high = 1000000000;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        cout << mid << endl;

        char response;
        cin >> response;

        if (response == '=') {
            break;
        } else if (response == '<') {
            low = mid + 1;
        } else if (response == '>') {
            high = mid - 1;
        }
    }

    return 0;
}
