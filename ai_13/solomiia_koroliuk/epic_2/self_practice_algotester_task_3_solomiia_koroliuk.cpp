/* Task 1911: Zenyk's Magic Tricks */

#include <iostream>
#include <cmath>

using namespace std;

int main(){
    
    int n, m;
    cin >> n >> m;

    int r = (pow(((((((n*n) + 4 ) * 14) / 7) - 8) * 50),  0.5) + 47) - (10 * n);

    if (r == m){
        cout << "Magic" << endl;
    }
    else{
        cout << "Too much juice" << endl;
    }


    return 0;
}
