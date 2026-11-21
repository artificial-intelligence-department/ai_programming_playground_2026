/*  Lab 3 Task 1 Variant 18
    Автор:Пилип'як Олег Васильович
    Група: ШІ-12, 3-тя група */

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a=0.1;
    double b=0.8;
    int k=10;
    double step=(b-a)/k;
    int n=50;
    double E=0.0001;
    for(int i=0;i<=k;i++){
        double x=a+step*i;
        double SN=0;
        for(int j=1;j<=n;j++){
            double a_n=cos(2*j*x)/(4.0*j*j-1);
            SN+=a_n;
        }
        double SE=0;
        int j=1;
        double a_e=cos(2*j*x)/(4.0*j*j-1);
         while ((a_e<0? -a_e:a_e) >=E){
            SE+=a_e;
            j++;
            a_e=cos(2*j*x)/(4.0*j*j-1);
            }
        double Y=0.5-(M_PI/4.0)*sin(x);
        cout << "X= " << x << "  SN= " << SN << "  SE= " << SE << "  Y= " << Y << endl;
        }
        return 0;
}