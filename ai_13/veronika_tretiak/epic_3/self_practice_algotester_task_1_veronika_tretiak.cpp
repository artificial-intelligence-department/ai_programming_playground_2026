#include <iostream>

using namespace std;

int main() {
    int n;
    long long m;
    cin >> n >> m;

    long long sum = 0;

    for(int i = 0; i < n; i++){
        long long a;
        cin >> a;

        long long x = a % m;
        sum = (sum + x * x) % m;
    }

    if(sum == 0){
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
    return 0;
    
}
