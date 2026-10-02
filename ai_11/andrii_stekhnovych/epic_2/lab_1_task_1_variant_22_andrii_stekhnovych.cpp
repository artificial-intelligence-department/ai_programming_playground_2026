#include <iostream>
#include<math.h>
using namespace std;
int main(){
    {
        // Обчислення за формулою для float
        float a=100.0;
        float b=0.001;
        float c_1=pow(a-b, 4);
        float c_2=pow(a, 4)-4*pow(a, 3)*b;
        float c=c_1-c_2;
        float d=6*pow(a, 2)*pow(b,2)-4*a*pow(b, 3)+pow(b, 4);        
        cout << "float: " << c/d << endl;
    }
    {
        // Обчислення за формулою для double
        double a=100;
        double b=0.001;
        double c_1=pow(a-b, 4);
        double c_2=pow(a, 4)-4*pow(a, 3)*b;
        double c=c_1-c_2;
        double d=6*pow(a, 2)*pow(b,2)-4*a*pow(b, 3)+pow(b, 4);  
        cout << "double: " << c/d << endl;
    }


}