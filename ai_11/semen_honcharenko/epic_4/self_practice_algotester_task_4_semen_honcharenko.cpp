/*
    Алготестер. "Will he help or blow it off?"
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
using namespace std;

int main() {
    int n = 0;
    string s = "0";
    int count = 0;
    cin >> n;
    cin >> s;
    int length = s.length();

    for (int i = 0; i <= length-6; i++) {
        if (s[i] == 'T'
        and s[i+1] == 'O'
        and s[i+2] == 'I'
        and s[i+3] == 'L'
        and s[i+4] == 'E'
        and s[i+5] == 'T') {
            count++;
            i += 5;
        }
    }
    if (count >= n) {
        cout << "YES\n";
    }
    else {
        cout << "NO\n";
    }
    return 0;
}
