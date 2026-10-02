#include <iostream>
using namespace std;

int main(){
    long long n;
    cin >> n;
    
    int num[9] = {500, 200, 100, 50, 20, 10, 5, 2, 1};
    int count = 0;
    
    for (int i = 0; i < 9; i++){
        count += n/num[i];
        n = n % num[i];
    }
    cout << count;
    return 0;
    }
