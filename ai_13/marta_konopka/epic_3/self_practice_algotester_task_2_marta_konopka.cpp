#include <iostream>
using namespace std;

int main(){
    int n;
    long long m;
    long long b = 0;
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        long long a;
        cin >> a;
        a %= m;
        b = (b + a * a) % m; 
    }
    if(b == 0){
        cout << "Yes";
    }
    else{
        cout << "No";
    }
    return 0;
}