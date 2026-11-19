//Акумулятори
#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    char c;
    cin >> n;
    cin >> c;
    string best;
    bool first = true;
    for (int k = 0; k < n; k++) {
        string s;
        cin >> s;
        int p = 0;
        while (p < s.length() && s[p] <= c)
        p++;
        string cand = s;
        cand.insert(p, 1, c);
        if (first || cand < best) {
            best = cand;
            first = false;
            }
        
    }
        cout << best << endl;
    
    
    return 0;
}