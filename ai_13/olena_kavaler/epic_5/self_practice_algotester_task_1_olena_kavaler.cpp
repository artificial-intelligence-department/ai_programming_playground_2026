
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
#include <string>
using namespace std;

bool match(const string &s, const string &t, int pos) {
    if (pos < 0 || pos + (int)t.length() > (int)s.length()) {
        return false;
    }
    return s.compare(pos, t.length(), t) == 0;
}

int main() {
    int tests;
    cin >> tests;

    for (int q = 0; q < tests; q++) {
        string s, t;
        cin >> s >> t;

        int d = (int)s.length() - (int)t.length();
        bool sergei;

            if (d % 2 == 1) {
            int mid = (d - 1) / 2;
            sergei = match(s, t, mid) && match(s, t, mid + 1);
        } else {
            int mid = d / 2;
            sergei = match(s, t, mid) || (match(s, t, mid - 1) && match(s, t, mid + 1));
        }

                if (sergei) {
            cout << "Sergei" << endl;
        } else {
            cout << "Larry" << endl;
        }
    }
    return 0;
}