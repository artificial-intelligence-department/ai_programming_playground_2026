// Algotester Lab 3, варіант 3: компресія стрічки
// приклад: AAAABBBCQQQQ -> A4B3CQ4
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;

    string result = "";
    int n = s.length();

    int i = 0;
    while (i < n) {
        char current = s[i];
        int count = 0;

        while (i < n && s[i] == current) {
            count++;
            i++;
        }

        result += current;
        if (count > 1) {
            result += to_string(count);
        }
    }

    cout << result << endl;

    return 0;
}