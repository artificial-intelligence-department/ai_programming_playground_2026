#include <iostream>

using namespace std;

int main(){
    
    int a, b;

    cin >> a >> b;
    
    if ((a < b) && ((b - a) != 1)){
        cout << a + 1;
    }
    else if ((b < a) && ((a - b) != 1)) {
        cout << b + 1;
    }
    else {
        cout << -1;
    }
    

    return 0;
    
}
