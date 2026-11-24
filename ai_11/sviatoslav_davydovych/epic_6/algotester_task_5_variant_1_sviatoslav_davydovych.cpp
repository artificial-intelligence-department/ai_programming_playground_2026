#include <iostream>
#include <iomanip>

using namespace std;

using ll = unsigned long long;

int main(){
    ll a, N;
    cin >> a >> N;

    for (int i = 0; i<N; i++){
        ll k, m;
        cin >> k >> m;
        k--; m--;
        for (int f = 0; f<8; f++){
            a ^= (1ULL << (8*k+f));
        }
        for (int f = 0; f<8; f++){
            a ^= (1ULL << (8*f+m));
        }
        a ^= (1ULL << (8*k+m));
    }
    cout << a;
}