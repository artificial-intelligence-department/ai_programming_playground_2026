#include <iostream>
using namespace std;
int main()
{
    long long H, M, h1, m1, h2, m2, h3, m3;
    cin >>H >>M >>h1 >>m1 >>h2 >>m2 >>h3 >>m3;
    if((H-h1-h2-h3)>0 && (M-m1-m2-m3)>0 && h1*m1==0 && h2*m2==0 && h3*m3==0 
    && h1>=0 && m1>=0 && h2>=0 && m2>=0 && h3>=0 && m3>=0 && (h1+m1)>0 && (h2+m2)>0 && (h3+m3)>0)
    {
        cout <<"YES";
    }
    else
    {
        cout <<"NO";
    }
    return 0;
}