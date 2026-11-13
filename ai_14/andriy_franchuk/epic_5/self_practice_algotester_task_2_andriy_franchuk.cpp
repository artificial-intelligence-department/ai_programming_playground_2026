#include <iostream>
#include <string>

using namespace std;

int main(){
    long n, m, s4 = 0, t4 = 0;
    string s, t;
    cin >> n >> m >> s >> t;

    for(int i = 0; i < n; i++){
        if(s[i]=='4'){
            s4++;
        }
    }
    long s7 = n - s4;

    for(int i = 0; i < m; i++){
        if(t[i]=='4'){
            t4++;
        }
    }
    long t7 = m - t4;

    long a = (m+1)*(n+1);
    long b = (s4*t4+s7*t7);
    long result = a - b - 1;

    cout << result;
}