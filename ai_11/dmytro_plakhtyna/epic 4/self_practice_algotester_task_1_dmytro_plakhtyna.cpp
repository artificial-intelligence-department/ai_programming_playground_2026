//Печиво
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int cakes[100000];
    long long sum = 0;
    for(int i = 0; i < n; i++) {
        cin >> cakes[i];
        if (cakes[i] == 0) {
            continue;
        }
        sum += cakes[i] - 1;
        
    }
    cout << sum;
    
}

