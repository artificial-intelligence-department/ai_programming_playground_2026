// Зуби
#include <iostream>
using namespace std;

int main(){
        long long n, k;
        long long best = 0, current = 0;
        cin >> n;
        cin >> k;
        for (int i =0; i < n; i++){
                long long a;
                cin >> a;
                if (a >= k) {
                        current++;
                        if (current > best) best = current;
                }
                else current = 0;
                
        }
        cout << best << endl;
        return 0;
}