#include <iostream>
using namespace std;

int main (){
int  m, n;
cin >> m;
cin >> n;
if (n < 0 || m < 0){
    cout << "Неприпустимі дані";
    return 0;
}else{
    if (m%2==0 || n%2==0){
        cout << "Dragon";
    }else {
        cout << "Imp";
    }
}
return 0;
}