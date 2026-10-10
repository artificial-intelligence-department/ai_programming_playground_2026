#include <iostream>
using namespace std;

int main(){
    int a, b, c;
    int money;
    cin >> a >> b >> c;
    if (a < 1 || a > 5000 || b < 1 || b > 5000 || c < 1 || c > 5000){
        return 1;
    }
    if (a < b){
        money = a + c;
    }
    else{
        money = a;
    }
    cout << money << endl;
    return 0;
}