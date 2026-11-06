/*
Алготестер, Завдання 3, Варіант 3
Станіслав Коваль
ШІ-12
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    string S;
    cin >> S;
    char c = S[0];
    string result = "";
    int count = 0;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] == c) {
            count++;
        } else {
            result += c;
            if (count > 1) {
                result += to_string(count);
            }
            c = S[i];
            count = 1;
        }

    }
    
    result += c;
    if (count > 1) {
        result += to_string(count);
    }

    cout << result << endl;
}