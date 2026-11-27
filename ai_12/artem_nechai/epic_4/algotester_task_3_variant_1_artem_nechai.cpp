#include <iostream>
#include <cstring>

using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore(256, '\n');

    int count = 0;
    constexpr int input_max = 42 * 42 + 41 + 1;
    char input[input_max];

    for (int i = 0; i < n; ++i) {
        cin.getline(input, input_max);

        int last_wrong_word_j = -2;
        int length = strlen(input);
        for (int j = 0; j < length; ++j) {
            if (input[j] == '#') {
                if (j != last_wrong_word_j + 1) {
                    count++;
                }
                last_wrong_word_j = j;
            }
        }
    }

    cout << count;

    return 0;
}