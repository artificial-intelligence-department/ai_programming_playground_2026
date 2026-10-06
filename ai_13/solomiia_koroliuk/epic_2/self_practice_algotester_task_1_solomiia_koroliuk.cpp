/* Task 2251: Chocolate Distribution */

#include <iostream>

using namespace std;

int main(){
    
    int a, b, c;
    
    cin >> a;
    cin >> b;
    cin >> c;
    
    if ((a * b) % c == 0){
        cout << "Yes";
    }
    else{
        cout << "No" << endl;
    }
    
    return 0;
}

