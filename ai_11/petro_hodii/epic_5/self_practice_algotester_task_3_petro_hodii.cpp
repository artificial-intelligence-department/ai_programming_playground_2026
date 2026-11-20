
#include <iostream>
#include <string>

using namespace std;

long long countWithoutSix(long long n) {
    if (n < 0) return 0;
    string s = to_string(n);
    int len = s.length();
    
    long long ans = 0;
    bool has_six = false;
    
    for (int i = 0; i < len; i++) {
        int digit = s[i] - '0';
        int remaining_digits = len - i - 1;
        
        long long pow9 = 1;
        for (int j = 0; j < remaining_digits; j++) {
            pow9 *= 9;
        }
        
        for (int d = 0; d < digit; d++) {
            if (d == 6) continue;
            ans += pow9;
        }
        
        if (digit == 6) {
            has_six = true;
            break;
        }
    }
    
    if (!has_six) {
        ans++;
    }
    
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long a, b;
    if (cin >> a >> b) {
        long long result = countWithoutSix(b) - countWithoutSix(a - 1);
        cout << result << "\n";
    }
    
    return 0;
}