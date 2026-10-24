#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a = 1;
    double b = 2;
    int k = 10;
    double krok = (b - a) / k;

    double eps = 0.0001;
    int maxn = 15;
    double x = 1;

    for(x = a; x <= b + eps; x += krok){
        double SN = 1;
        double an = 1;

        for(int n = 1; n <= maxn; n++){
          
         an = an * (x/n); 
         SN += an;
     
    }
    double SE = 1;
    an = 1; 
    int n1 = 1;

        while(an >= eps){
        an = an * (x/n1);
        SE += an;
        n1++;
     }
     double y = exp(x);
     
cout << "X = " << x << "  SN = " << SN << "  SE = " << SE << "  Y = " << y << "\n";
    
}
return 0;
}