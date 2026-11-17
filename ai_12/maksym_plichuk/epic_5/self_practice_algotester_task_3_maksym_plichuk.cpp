#include <iostream>
#include <string>

using namespace std;

int main() {

    int n;
    cin >> n;   

    char c;
    cin >> c;

    string bestName = "";

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        int pos = s.length();
        for (int j = 0; j < s.length(); j++) {
            if (s[j] > c) {
                pos = j;
                break;
            }
        }
        string candidate = s.substr(0, pos) + c + s.substr(pos);

        if (i == 0 || candidate < bestName) {
            bestName = candidate;
        }
    }

    cout << bestName << endl;

    return 0;
}
