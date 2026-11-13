#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    string text;
    getline(cin, text); //залишок першого рядка після числа N

    long long rituals = 0;

    for (int i = 0; i < n; ++i) {
        string r;
        getline(cin, r);
        
        bool in_block = false; // чи знаходиться в блоці 
        for (char c : r) { // символ c в рядках r
            if (c == '#') {
                if (!in_block) {
                    rituals++;
                    in_block = true;
                }
            } else {
                in_block = false;
            }
        }
    }

    cout << rituals << endl;

    return 0;
}