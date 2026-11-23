#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
    const int k=10,N=3;
    const double a=0.1,b=0.8,e=0.0001,st=(b-a)/k;
    double x,SN=0,SE=0,xpow,t,y;
    cout<<fixed<<setprecision(6);
    for(int i=0;i<=k;i++){
        x=a+i*st;
        xpow=pow(x,4);
        SN=0;
        double c=x;
        for(int n=0;n<=N;n++){
            SN+=c/(4*n+1);
            c*=xpow;
        }
        SE=0;
        int n=0;
        c=x;
        t=c;
        while(t>=e){
            SE+=t;
            n++;
            c*=xpow;
            t=c/(4*n+1);
        }
        y=0.25*log((1+x)/(1-x))+0.5*atan(x);
        cout<<"X="<<x<<"    SN="<<SN<<"    SE="<<SE<<"    Y="<<y<<endl;
    }
}