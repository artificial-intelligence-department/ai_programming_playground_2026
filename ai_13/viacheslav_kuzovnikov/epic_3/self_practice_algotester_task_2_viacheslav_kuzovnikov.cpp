/*
Літаюча камера
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main (){
    int a = 0;
    int b = 0;
    cin >> a;
    cin >> b;
    if (a < 0 || a > 1000){
        return 1;
    }
    if (b < 0 || b > 1000){
        return 1;
    }
    float c = sqrt(pow(a,2)+pow(b,2));
    cout << fixed << setprecision(2) << c;
    return 0;
}
