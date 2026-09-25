#include <iostream>
#include <string>
using namespace std;

int main(){
    char a;
    cin >> a;

    if(a>='a' && a<= 'z')
        cout << a - 96;
    else if (a>='A' && a<= 'Z')
        cout << a - 64;

    else if(a>='0' && a<='9')
        cout << "digit";

    else
        cout << "weird symbol";

    return 0;
}