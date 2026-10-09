#include <iostream>
using namespace std;

int main(){
    int t;
    cin >> t;
    while (t--){
        long long n, m;
        cin >> n >> m;

        if ( n > m) {
            swap(n, m);
        }
        if( n > 1){
            cout << 0 << endl;
        }
        else if( m % 2 == 1){
            cout << 3 << endl;
        }
        else{
            cout << 2 << endl;
        }
            }
            return 0;
        }