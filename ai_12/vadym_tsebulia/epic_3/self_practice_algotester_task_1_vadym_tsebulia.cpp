// Марічка і печиво
#include <iostream>
using namespace std;

int main(){
        long long n;
        long long a;
        long long sum = 0;
        cin >> n;
        for(int i = 0; i < n; i++){
                cin >> a;
                if (a <= 0) continue;
                else sum += a - 1;
        }
        cout << sum << endl;
        return 0;
}