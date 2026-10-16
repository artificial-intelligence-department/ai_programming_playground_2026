/*
Назва задачі: Фінансова грамотність
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int numbers[100000];
    int oddIndex = -1;

    for (int i = 0; i < n; i++) {
        cin >> numbers[i];

        if (numbers[i] % 2 != 0) {
            oddIndex = i;
        }
    }

    if (oddIndex == -1) {
        cout << "NO" << endl;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (i != oddIndex && numbers[i] % 2 != 0) {
            cout << "NO" << endl;
            return 0;
        }
    }

    cout << "YES" << endl;
    cout << numbers[oddIndex];

    for (int i = 0; i < n; i++) {
        if (i != oddIndex) {
            cout << " " << numbers[i];
        }
    }

    cout << endl;

    return 0;
}
