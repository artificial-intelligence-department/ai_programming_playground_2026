#include <iostream>
#include <string>
using namespace::std;
// щасливі рядки
int main () {
    long long n,m;
    string s,t;
    long long s_4 = 0;
    long long s_7 = 0;
    long long t_4 = 0;
    long long t_7 = 0;
    int l;
    cin >> n;
    cin >> m;
    cin >> s;
    cin >> t;
    if (n > m) l = n;
    else l = m;
    for (int i = 0; i < l; i++) {
        if (i < n) {
            if (s[i] == '4') s_4++;
            else s_7++;
        }
        if (i < m) {
            if(t[i] == '4') t_4++;
            else t_7++;
        }
    }
    long long result = (n + 1) * (m + 1) - 1;
    result = result - s_4 * t_4 - s_7 * t_7;
    cout << result;
}