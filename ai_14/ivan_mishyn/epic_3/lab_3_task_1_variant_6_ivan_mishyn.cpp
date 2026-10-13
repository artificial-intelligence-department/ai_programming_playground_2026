#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main(){
    cout << fixed << setprecision(8);
    const double pi = 3.14159265358979323846;
    const double epsilon = 0.0001;
    for(double x=0.1;x<1;x+=0.09){
        cout<<"X="<<x;
        double sn=1;
        double c=1;
        for (int n = 1; n <= 25; n++) {
            c=c*(x/n);
            sn+=cos(n * pi / 4)*c;
        }
        c=1;
        int n=1;
        double se=1;
        while(fabs(c)>epsilon){
            c=c*(x/n);
            se+=cos(n * pi / 4)*c;
            n++;
        }
        double Y = exp(x*cos(pi/4)) * cos(x*sin(pi/4));
        cout<<"  SN="<<sn<<"  SE="<< se<<"  Y="<< Y<<"\n";
    }
    
    return 0;
}