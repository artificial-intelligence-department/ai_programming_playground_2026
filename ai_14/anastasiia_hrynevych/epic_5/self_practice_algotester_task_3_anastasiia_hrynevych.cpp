#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;
    int count = 0;
    while (cin >> str) {
        string newstr = str;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] >= 'A' && str[i] <= 'Z') str[i] = str[i] + 32;
            newstr[str.length() - i - 1] = str[i];
        }
        if (newstr == str) count++;
    }
    cout << count << endl;

}