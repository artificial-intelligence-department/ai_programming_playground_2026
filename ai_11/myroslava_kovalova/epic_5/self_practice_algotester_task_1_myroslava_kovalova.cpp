#include <iostream>
#include <string>

using namespace std;

int main() {
    int tests;
    cin >> tests;

    for (int i = 0; i < tests; i++) {
        string s, f;
        cin>>s>>f;

        int n = s.size();
        int m = f.size();
        int k = n - m;
	    bool sergWins;
        if (k <= 0) {
            sergWins = (s == f);
        
        }else if (k % 2 == 1) {
            int r = (k + 1) / 2;
            sergWins = (s.compare(r - 1, m, f) == 0) && (s.compare(r, m, f) == 0);
        } else {
            int r = k / 2;
            sergWins = (s.compare(r, m, f) == 0)|| ((s.compare(r - 1, m, f) == 0) && (s.compare(r + 1, m, f) == 0));
        }

        if (sergWins){
            cout << "Sergei" << endl;
        } else {
            cout << "Larry" << endl;
        }
    }

    return 0;
}