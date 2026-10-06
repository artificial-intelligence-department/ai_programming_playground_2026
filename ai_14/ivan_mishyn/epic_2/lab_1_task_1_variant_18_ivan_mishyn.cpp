#include <iostream>
#include <cmath>

using namespace std;

int main(){
    {
        float a=1000;
        float b=0.0001;
        float c_1 =pow(a-b,3);
        float c_2 =pow(a,3);
        float c= c_1 - c_2;
        float d_1 = pow(b, 3);
        float d_2 = 3*a*pow(b,2);
        float d_3 = 3*pow(a,2)*b;
        float d=d_1-d_2-d_3;
        float result = c/d;
        cout<<"Float: "<<result<<endl;
    }
    {
        double a=1000;
        double b=0.0001;
        double c_1 =pow(a-b,3);
        double c_2 =pow(a,3);
        double c= c_1 - c_2;
        double d_1 = pow(b, 3);
        double d_2 = 3*a*pow(b,2);
        double d_3 = 3*pow(a,2)*b;
        double d=d_1-d_2-d_3;
        double result = c/d;
        cout<<"Double: "<<result<<endl;
    }
    return 0;
}