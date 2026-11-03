/*Task 3 algotester variant 3
Ім'я: Сукач Андрій
Група: ШІ-14*/
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    string compressed = "";
    char current = s[0]; // поточний символ
    int count = 1;
    for (int i = 1; i < s.length(); i++) {
        if (s[i] == current) {
            count++;
        } else {
            if (count > 1) {
                compressed += current + to_string(count);
            } else {
                compressed += current;
            }
            current = s[i];
            count = 1;
        }
    }
    if (count > 1) {
        compressed += current + to_string(count);
    } else {
        compressed += current;
    }
    cout << compressed << endl;
    return 0;
}