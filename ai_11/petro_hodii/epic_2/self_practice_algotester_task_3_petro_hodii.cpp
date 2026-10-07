#include <iostream>

using namespace std;

int main(){

    char a;

    cin >> a;

    if(a >= '0' && a <= '9'){
        cout << "digit";
    }
    else if(a >= 'A' && a <= 'Z'){
        cout << int(a)-64;
    }
    else if(a >= 'a' && a <= 'z'){
        cout << int(a)-96;
    }
    else{
        cout << "weird symbol";
    }
    return 0;
}