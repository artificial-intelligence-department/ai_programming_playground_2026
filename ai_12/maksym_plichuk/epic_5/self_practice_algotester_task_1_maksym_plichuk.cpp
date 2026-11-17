#include <iostream>
using namespace std;

int main(){

    int tests;
    string s1, s2;
    cin >> tests;

    for (int i = 0; i < tests; i++) {
        cin >> s1 >> s2;

        int n = s1.size();
        int m = s2.size();
        int k = n - m;

        if (k == 0) {
            cout << (s1 == s2 ? "Sergei\n" : "Larry\n");
        } else if (k % 2 == 1) {
            int start = (k - 1) / 2;
            bool left_ok = (s1.substr(start, m) == s2);
            bool right_ok = (s1.substr(start + 1, m) == s2);
            
            if (left_ok && right_ok) {
                cout << "Sergei" << endl;
            } else {
                cout << "Larry" << endl;
            }
        } else {
            int start = (k - 2) / 2;
            bool onlyRight = (s1.substr(start, m) == s2);
            bool center = (s1.substr(start + 1, m) == s2);
            bool onlyLeft = (s1.substr(start + 2, m) == s2);

            if ((onlyRight || center) && (center || onlyLeft)) {
                cout << "Sergei\n";
            } else {
                cout << "Larry\n";
            }
        }
    }
    return 0;
}