//Снігурочка

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

int main() {
    string text;
    int count = 0;
    while (cin >> text) {
        for (size_t i = 0; i < text.size(); i++) text[i] = tolower(text[i]);
        string r = text;
        reverse(r.begin(), r.end());
        if (r == text) count++;
    }
    cout << count << endl;
    return 0;
}