/*
Назва задачі: Цікаве листування
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    char s[10][10];
    int n = 0;

    cin >> n;

    int k = sqrt(n);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            cin >> s[i][j];
        }
    }

    for(int d = 0; d < (k * 2) - 1; d++) {
        for (int i = 0; i < k; i++) {
            int j = d - i;
            if (j < k && j >= 0) {
                cout << s[i][j];
            }
        }
    }

    return 0;

}