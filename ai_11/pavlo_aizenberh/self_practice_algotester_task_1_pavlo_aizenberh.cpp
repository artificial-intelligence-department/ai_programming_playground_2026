#include <iostream>
using namespace std;

int main(){
    int n;
    int m;
    int k;

    cin >> k >> m >> n;
    
    if (((m+n) % k) == 1){
        cout << "No";
        return 1;
    }
    cout << "Yes";
    return 0;
}