// Задача №0191 "Торт для Петрика"
#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int r, n;
    cin>>n>>r;
    /*pi*rsmall^2=pi*r^2/n, бо у найбільшому шарі містяться всі 
    площі кілець зверху
    rsmall=r/корінь n*/
    double rsmall;
    rsmall=r/sqrt((double)n);
    cout<<rsmall<<endl;
    return 0;
}