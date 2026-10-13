#include <iostream>
#include <cmath>
using namespace std;
int main(){
    double a=1*exp(-1);
    double sum=a;
    for (int n = 2; n <= 7; n++) {
        a *=pow((double)n / (n - 1), 2) * exp(sqrt(n - 1) - sqrt(n));
        sum += a;
    }
    cout<<sum<< endl;
    return 0;
}