/*
<Белаш Матвій ШІ-12
Завдання з алготестеру "Євро 2012"
*/

#include <iostream>
using namespace std;

int main(){

    int a[4];
    int sum = 0;
    for(int i = 0; i < 4; i++){
        cin >> a[i];
    }

    for(int i = 0; i < 4; i++){
        sum += a[i];
    }

    cout << sum;
    return 0;
}
