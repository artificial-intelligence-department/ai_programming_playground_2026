#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    cin >> s;
    int n = (int)s.size();
    long long cnt[26] = {0};
    for(int i = 0; i < n; i++){
        cnt[s[i] - 'a']++;
    }   
    for(int k = 1; k <= n; k++){
        long long q = n / k, r = n % k;
        long long M = 0, extra = 0;
        bool ok = true;
        for(int i = 0; i < 26; i++){
            long long a = cnt[i];
            if(a == 0) continue;
            long long m = a % q;
            if(m * (q + 1) > a){ ok = false; break; }
            M += m;
            long long B = a / (q + 1);
            extra += (B - m) / q;
        }
        if(!ok) continue;
        if(M <= r && extra >= (r - M) / q){
            cout << k << "\n";
            return 0;
        }
    }
    return 0;
}