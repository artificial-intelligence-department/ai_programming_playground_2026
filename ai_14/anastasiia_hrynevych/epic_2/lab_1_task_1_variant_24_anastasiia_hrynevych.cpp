#include <iostream>
using namespace std;

int main() {
    const float af = 1000, bf = 0.0001;
    float sumf = af + bf;
    float sum3f = sumf * sumf * sumf;
    float a3f = af * af * af;
    float ab2f =  af * bf * bf;
    float a2bf =  af * af * bf;
    float b3f = bf * bf * bf;
    float resf = ( sum3f - a3f )/( 3*ab2f + 3*a2bf + b3f );
    cout << "Результат обчислення виразу при типу даних float: " << resf << endl; 
    const double ad = 1000, bd = 0.0001;
    double sumd = ad + bd;
    double sum3d = sumd * sumd * sumd;
    double a3d = ad * ad * ad;
    double ab2d =  ad * bd * bd;
    double a2bd =  ad * ad * bd;
    double b3d = bd * bd * bd;
    double resd = ( sum3d - a3d )/( 3*ab2d + 3*a2bd + b3d );
    cout << "Результат обчислення виразу при типу даних double: " << resd << endl; 

}