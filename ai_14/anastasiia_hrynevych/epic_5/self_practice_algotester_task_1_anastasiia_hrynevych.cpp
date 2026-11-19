#include <iostream>
#include <string>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            {
    string str1, str2;
    cin >> str1 >> str2;

    int diff = str1.length() - str2.length();
    int m = diff / 2;
    int len = str2.length();

    
    auto check = [&](int i) {
        if (i < 0 || i > diff) return false;
        return str1.compare(i, len, str2) == 0;
    };

    bool sergei = false;

    if (diff % 2 == 1) { 
        if (check(m) && check(m + 1)) {
            sergei = true;
        }
    } else {             
        if (check(m) || (check(m - 1) && check(m + 1))) {
            sergei = true;
        }
    }

    if (sergei) {
        cout << "Sergei\n";
    } else {
        cout << "Larry\n";
    }
}
        }
    }
    return 0;
}