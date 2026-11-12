#include <iostream>
#include <string>
using namespace std;
int main() {
    long long n= 0;
    long long m = 0;;
    cin >> n >> m;
    string s; 
    string t;
    cin >> s >> t;
    long long zagal = (n + 1) * (m + 1);
    long long povt = 0;
    
    long long k4 = 0;
    long long k7 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '4') {
            k4++;
        }
        else if (s[i] == '7') {
            k7++;
        }
    }
    long long f4 = 0;
    long long f7 = 0;
    for (int j = 0; j < m; j++) {
        if (t[j] == '4'){
            f4++;
        }
        else if (t[j] == '7'){
            f7++;
        }
    }
    povt = (k4 * f4) + (k7 * f7);
    cout << zagal - povt - 1;
    return 0;
}
