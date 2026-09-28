#include <iostream>
using namespace std;
int main(){
    int n,m;
    cin >> n >> m;
    int quantity=n*m;
    if (quantity%2==0) {
        cout << "Dragon";
    } else {
        cout << "Imp";
    }
    return 0;
}