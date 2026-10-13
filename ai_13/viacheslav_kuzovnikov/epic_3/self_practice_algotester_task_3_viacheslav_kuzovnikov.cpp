/*
Політ на Марс
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
#include <iomanip>
using namespace std;
int main (){
    long long a = 0;
    cin >> a;
    if ( a < 1 || a > 10000000000){
        return 1;
    }
    float b = 225000000;
    float c = b/a;
    cout << fixed << setprecision(6) << c;

    return 0;
}