/*
Електронний годинник
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
using namespace std;
int main (){
    int n = 0;
    cin >> n;
    if  (n < 0 || n > 31999){
        return 1;
    }

    int h = (n/60)%24;
    if (h < 0 || h > 23){
        return 1;
    }
    int m = n%60;
    if (m < 0 || m > 59){
        return 1;
    }
    cout << h << " " << m << endl;


    return 0;
}