#include <iostream>

using namespace std;

int main(){
    
    int a, b, c, sum;

    cin >> a >> b >> c;

    sum = a+b;
    
    if (sum > c){
        cout << "YES";
    }
    else {
        cout << "NO";
    }
    
    return 0;
    
}
