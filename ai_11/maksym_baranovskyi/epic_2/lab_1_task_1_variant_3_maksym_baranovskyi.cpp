#include <iostream>
#include <cmath>

using namespace std;

int main(){

    float a1 = 1000;
    float b1 = 0.0001;

    float sumABf = a1 + b1;
    float part1f = pow(sumABf, 3);
    float part2f = pow(a1, 3);
    float part3f = 3 * pow(a1, 2) * b1;
    float enumeratorf = part1f - (part2f + part3f);

    float part4f = 3 * a1 * pow(b1, 2);
    float part5f = pow(b1, 3);
    float denominatorf = part4f + part5f;

    float floatResult = enumeratorf/denominatorf;
    cout << "Float result: " << floatResult << endl;

    double a2 = 1000;
    double b2 = 0.0001; 

    double sumABd = a2 + b2;
    double part1d = pow(sumABd, 3);
    double part2d = pow(a2, 3); 
    double part3d = 3 * pow(a2, 2) * b2;
    double enumeratord = part1d - (part2d + part3d);

    double part4d = 3 * a2 * pow(b2, 2);
    double part5d = pow(b2, 3);
    double denominatord = part4d + part5d;
    
    double doubleResult = enumeratord/denominatord;
    cout << "Double result: " << doubleResult << endl;

    return 0;
}