/* Task 1872: Складний екзамен */

#include <iostream>

using namespace std;

int main(){
    
    int n;
    cin >> n;

    bool f = false;
    while (n > 0){
        if (n % 100 == 47){
            f = true;
            break;
        }
        n /= 10;
    }

    if (f){
        cout << "YES";
    } 
    else {cout << "NO";}
    
    return 0;
}

