#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    float a_float=1000;
    float b_float=0.0001;
    float s1_float=pow(a_float-b_float, 3);
    float s2_float=pow(a_float, 3);
    float s3_float=pow(b_float, 3);
    float s4_float=3*a_float*pow(b_float, 2);
    float s5_float=3*pow(a_float, 2)*b_float;
    
    float s6_float=s1_float-s2_float;
    float s7_float=s3_float-s4_float-s5_float;
    float s_float=s6_float/s7_float;


    double a_double=1000;
    double b_double=0.0001;
    double s1_double=pow(a_double-b_double, 3);
    double s2_double=pow(a_double, 3);
    double s3_double=pow(b_double, 3);
    double s4_double=3*a_double*pow(b_double, 2);
    double s5_double=3*pow(a_double, 2)*b_double;
    
    double s6_double=s1_double-s2_double;
    double s7_double=s3_double-s4_double-s5_double;
    double s_double=s6_double/s7_double;
    cout <<"float:" <<endl;
    cout <<s_float <<endl;
    cout <<endl;
    cout <<"double:" <<endl;
    cout <<s_double <<endl;
}