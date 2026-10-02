#include <iostream>

using namespace std;

int main(){

    int a,b,c;

    cin >> a >> b >> c;

    if(a+b <= 47 || a+c <= 47 || b+c <= 47){
        cout << "YES";
    }
    else{
        cout << "NO";
    }
    return 0;
}
