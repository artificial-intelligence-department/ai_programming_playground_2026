#include <iostream>
#include <string>
using namespace std;

int main() {
    int k;
    string s;

    cin >> k >> s;

    int count = 0;
    
    size_t pos = s.find("TOILET");

    while (pos != string::npos) {
        count++;
        pos = s.find("TOILET", pos + 6);
    }

    if (count >= k) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}