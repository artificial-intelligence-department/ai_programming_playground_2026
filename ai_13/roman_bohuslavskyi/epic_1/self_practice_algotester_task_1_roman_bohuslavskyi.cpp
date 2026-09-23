#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int numbers[100];
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    int length[100];
    int answer = 1;

    for (int i = 0; i < n; i++) {
        length[i] = 1;

        for (int j = 0; j < i; j++) {
            if (numbers[j] < numbers[i]) {
                if (length[j] + 1 > length[i]) {
                    length[i] = length[j] + 1;
                }
            }
        }

        if (length[i] > answer) {
            answer = length[i];
        }
    }

    cout << answer << endl;

    return 0;
}