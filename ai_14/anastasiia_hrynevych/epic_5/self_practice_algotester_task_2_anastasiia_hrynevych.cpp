#include <iostream>
#include <string>

using namespace std;

int main() {
    string str;
    cin >> str;
    int count[26] = {0};
    int len = str.length();
    int countall = 0, counteven = 0;
    for (int i = 0; i < len; i++) {
        count[str[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (count[i] > 0 && count[i] % 2 == 0) {
            counteven++;
            countall++;
        }
        else if (count[i] > 0 && count[i] % 2 == 1) {
            countall++;
        }
    }
    if (counteven == countall || counteven == countall - 1) cout << "YES\n";
    else cout << "NO\n";
    
}