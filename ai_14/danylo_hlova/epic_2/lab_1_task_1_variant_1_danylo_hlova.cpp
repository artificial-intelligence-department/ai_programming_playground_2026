#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
    // для float
    float af=1000;
    float bf=0.0001;

    float f1=pow(af+bf,2);
    float f2=pow(af,2)+2*af*bf;
    float f3=f1-f2;
    float f4=f3/pow(bf,2);
    cout<< "Result float: "<<f4<< endl;

    double ad=1000;
    double bd=0.0001;

    double d1=pow(ad+bd,2);
    double d2=pow(ad,2)+2*ad*bd;
    double d3=d1-d2;
    double d4=d3/pow(bd,2);
    cout<< "Result double: "<<d4<< endl;
    return 0;
}