
#include <iostream>
#include <cmath>
using namespace std;
int main () {
    float af = 100, bf = 0.001;
    // степені а і б для float
    float af2 = pow(af, 2);
    float af3 = pow(af, 3);
    float af4 = pow(af, 4);
    float bf2 = pow(bf, 2);
    float bf3 = pow(bf, 3);
    float bf4 = pow(bf, 4);
    // обчислення чисельника,знаменника і результату для float
    float cf = pow(af - bf, 4) - (af4 - 4 * af3 * bf);
    float zf = 6 * af2 * bf2 - 4 * af * bf3 + bf4;
    float rf = cf/zf;

    double ad = 100, bd = 0.001;
    // степені а і б для double
    double ad2 = pow(ad, 2);
    double ad3 = pow(ad, 3);
    double ad4 = pow(ad, 4);
    double bd2 = pow(bd, 2);
    double bd3 = pow(bd, 3);
    double bd4 = pow(bd, 4);
    // обчислення чисельника,знаменника і результату для double
    double cd = pow(ad - bd, 4) - (ad4 - 4 * ad3 * bd);
    double zd = 6 * ad2 * bd2 - 4 * ad * bd3 + bd4;
    double rd = cd/zd;
    //вивід результатів
    cout.precision(15);
    cout << " float: " << rf << endl;
    cout << " double: " << rd << endl;

    return 0;
}