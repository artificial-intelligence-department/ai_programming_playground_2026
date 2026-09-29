#include <iostream>

using namespace std;

int main(){
    int n, m, k, c;
    cin >> n >> m >> k;
    c = n*m;
    if (c % k == 0){
        cout << "Yes";
    }
        else {
        cout << "No";
         }
    return 0;
}
