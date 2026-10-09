#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    float af = 1000;
    float bf = 0.0001f;
    float sq1f = (af - bf) * (af - bf);
    float sq2f = af * af - 2 * af * bf;
    float resf = (sq1f - sq2f) / (bf * bf);

    double ad = 1000;
    double bd = 0.0001;
    double sq1d = (ad - bd) * (ad - bd);
    double sq2d = ad * ad - 2 * ad * bd;
    double resd = (sq1d - sq2d) / (bd * bd);

    cout << "Float: " << resf << endl;
    cout << "Double: " << resd << endl;

    return 0;
}
