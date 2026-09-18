#include <iostream>

using namespace std;

int main(){
    
    int n;
    long long sum = 0;
    cin >> n;
    
    for(int i = 0; i < n; i++){
        long long cookies;
        cin >> cookies;
        sum += (cookies-1);      
    }
    cout << sum;
    
    return 0;
}


