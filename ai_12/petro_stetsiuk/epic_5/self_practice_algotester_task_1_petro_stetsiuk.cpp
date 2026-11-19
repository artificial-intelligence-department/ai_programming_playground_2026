// Фібонета
#include <iostream>

using namespace std;

int main()
{
    long long n,a1,a2,go=1,temp;
    cin>>n>>a1>>a2;
    if(n==0&&a1==0){cout<<0;return 0;}
    else if(n==0&&a1>0){cout<<"+";return 0;}
    else if(n==0&&a1<0){cout<<"-";return 0;}
    if(n==1&&a2==0){cout<<0;return 0;}
    else if(n==1&&a2>0){cout<<"+";return 0;}
    else if(n==1&&a2<0){cout<<"-";return 0;}
    if(a1==0&&a2==0){cout<<0;return 0;}
    else if(a1>=0&&a2>=0){cout<<"+";return 0;}
    else if(a1<=0&&a2<=0){cout<<"-";return 0;}
    else
    {
        while(go!=n)
        {
            temp=a1+a2;
            a1=a2;
            a2=temp;
            go++;
            if(go < n) 
            {
                if(a1>=0&&a2>=0){cout<<"+";return 0;}
                else if(a1<=0&&a2<=0){cout<<"-";return 0;}
            }
        }
        if(temp>0){cout<<"+";return 0;}
        else if(temp==0){cout<<0;return 0;}
        else if(temp<0){cout<<"-";return 0;}
    }
}