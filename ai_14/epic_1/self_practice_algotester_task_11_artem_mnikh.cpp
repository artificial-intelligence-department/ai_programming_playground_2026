#include <iostream>

using namespace std;
int main(){
    long long result = 0;
    int a;
    cin >> a;
    for (int i = 0; a>i; i++){
        long long c;
        cin >> c;
        result += c - 1;
        
    }
    cout << result;
}