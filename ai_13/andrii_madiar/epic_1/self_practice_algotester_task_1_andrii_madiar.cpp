#include <iostream>
using namespace std;
int main(){
    int a=0, b=0;
    int a0=0, b0=0;
    cin >> a0 >> b0;
    if (a0<0 || a0>100){
      cout << "Неправильне введення" << endl;
     return 0;
    }
    else if (b0<0 || b0>100){
      cout << "Неправильне введення" << endl;
     return 0;
    }
    else a=a0, b=b0;
    int S=a+b;
    cout << S << endl;
    return 0;
}