#include <iostream>
using namespace std;
int main(){
    long  a, b, c, n, x1, xn;
    cin >> a >> b >> c >> n >> x1 >> xn;
    long  low = -1000000, hi = 1000000;
    while (low< hi) {
        long  mid = low + (hi - low) / 2;
        long  prev2 = x1;
        long  prev1 = mid;
        long  cur = prev1;
        for (int i = 3; i <= n; i++) {
            cur = a * prev1 + b * prev2 + c;
            if (cur > 2000000000 || cur < -2000000000) {
                if(cur > 0){
                    cur = 2000000000;
                }
                else{
                    cur = -2000000000;
                }
                break;
            }

            prev2 = prev1;
            prev1 = cur;
        }

        if (cur < xn)
            low = mid + 1;
        else
            hi = mid;
    }

    cout << low;
    return 0;
}
