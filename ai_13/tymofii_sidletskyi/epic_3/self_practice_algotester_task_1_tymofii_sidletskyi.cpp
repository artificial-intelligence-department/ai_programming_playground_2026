#include <iostream>
#include <string>
// Задача 0281
using namespace std;

int main() {

    string s;
    cin >> s;

    int unique_count = 0;

    for (size_t i = 0; i < s.length(); i++) {
        bool is_new = 1;

        for (size_t j = 0; j < i; j++) {
            if (s[i] == s[j]) {
                is_new = 0;
                break;
            }
        }

        if (is_new) {
            unique_count++;
        }
    }

    cout << unique_count << endl;

    return 0;
}