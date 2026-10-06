#include <iostream>
using namespace std;

int main(){
    int n = 5;
    long long prev = 0;

    for(int i = 0; i < n; i++){
        long long a;
        cin >> a;
        if(cin.fail() || a <= 0){
            cout << "ERROR";
            return 0;
        }
        if(i > 0 && a > prev){
            cout << "LOSS";
            return 0;
        }
        prev = a;
    }

    cout << "WIN";
    return 0;
}