#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    
    
    long long n;
    long long ans = 1000000000;
    cin >> n;

    long long steps = 0;
    
    

    while (n >= 1) {
        if ((n - 1) % 7 == 0) {
            long long step7 = steps + (n - 1) / 7;
            ans = min(ans, step7);
        }
        if (n == 1) {
            ans = min(ans, steps);
            break;
        } 
        
        
        else if (n % 4 == 0) {
            n /= 4;
            steps++;
        } 
        
        else {
            if (n - 7 < 1) {
                break;
            }
            n -= 7;
            steps++;
        }
    }

    if (ans == 1000000000) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}

