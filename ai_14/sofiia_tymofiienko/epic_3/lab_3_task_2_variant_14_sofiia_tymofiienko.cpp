#include <iostream>
#include <cmath>
using namespace std;

    int main(){
    
    int n=20;
    int m;

    const double PI = 3.141592653589793;
    double eps=0.0001;
    double a= PI/5;
    double b= PI;
    double h= (b-a)/10;
    double x;
    double Y;
    double SN=0;
    double SE;
    double term;

    for (int i=0; i<=10; i++){
        double x= a + i * h;
        Y= 0.25 * ((x*x- (PI*PI)/3.0));

            SN=0;
        for (int n=1; n<=20; n++){
            term= pow(-1, n) * cos(n*x)/(n*n);
            SN+=term;
        }
            SE=0;
            m=1;
            term= pow(-1, m) * cos(m*x)/(m*m);

            while (abs(term)>=eps){
                SE +=term;
                m++;
                term= pow(-1, m) * cos(m*x)/(m*m);
            }
        cout<<"  X= "<<x<< "  SN= "<<SN<<"  SE= "<<SE<<"  Y= "<<Y<<endl;
    }
        return 0;
}
