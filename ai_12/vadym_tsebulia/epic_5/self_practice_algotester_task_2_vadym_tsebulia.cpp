#include <iostream>
#include <string>
using namespace std;

int main(){
    long long n, m;
    cin >> n;
    cin >> m;

    string s, t;
    cin >> s;
    cin >> t;

    long long s4 = 0, t4 = 0;
    long long s7 = 0, t7 = 0;
    for (int i = 0; i < n; i++){
        if (s[i] == '4') s4++;
        else s7++;
    }

    for (int i = 0; i < m; i++){
        if (t[i] == '4') t4++;
        else t7++;
    }

    long long total = (n + 1) * (m + 1) - 1 - (s4 * t4 + s7 * t7);
    cout << total << endl;
    return 0;
}