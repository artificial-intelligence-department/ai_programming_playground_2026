#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

    //float part
    float a_f = 1000;
    float b_f = 0.0001f;
    float one_f = (a_f + b_f)*(a_f + b_f);
    float two_f = a_f*a_f + 2 * a_f * b_f;
    float three_f = one_f - two_f;
    float four_f = b_f*b_f;
    float res_f = three_f / four_f;
    
    cout << fixed << setprecision(8) << "float res: " << res_f << endl;

    //double part

    double a_d = 1000;
    double b_d = 0.0001;
    double one_d = pow((a_d + b_d), 2);
    double two_d = pow(a_d, 2) + 2 * a_d * b_d;
    double three_d = one_d - two_d;
    double four_d = pow(b_d, 2);
    double res_d = three_d / four_d;
    
    cout << fixed << setprecision(8) << "double res: " << res_d << endl << endl;

    return 0;
}