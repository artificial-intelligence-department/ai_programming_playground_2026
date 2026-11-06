#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    float af = 1000, bf = 0.0001f;
    float cf = pow(af - bf, 3);          
    float df = pow(af, 3);               
    float chyselnyk_f = cf - df;              
    float znamenyk_f = pow(bf, 3) - 3 * af * bf * bf - 3 * af * af * bf; 
    float result_f = chyselnyk_f / znamenyk_f;

    double ad = 1000, bd = 0.0001;
    double cd = pow(ad - bd, 3);
    double dd = pow(ad, 3);
    double chyselnyk_d = cd - dd;
    double znamenyk_d = pow(bd, 3) - 3 * ad * bd * bd - 3 * ad * ad * bd;
    double result_d = chyselnyk_d / znamenyk_d;

    cout << setprecision(15);
    cout << "float:  " << result_f << endl;
    cout << "double: " << result_d << endl;
    return 0;
}