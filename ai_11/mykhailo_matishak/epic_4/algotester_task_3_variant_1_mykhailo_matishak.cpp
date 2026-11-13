#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;
    string s;
    int ritual = 0;
    int flag = 0;

    while (cin >> s) {
        flag = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '#') {
                if (flag == 0) {
                    ritual++;
                }
                flag = 1;
            } else {
                flag = 0;
            }
        }
    }
    cout << ritual;
    
    return 0;
}