/*
    Задача: Algotester lab 1
    Варіант: 2
    Автор: Стецюк Петро
    Група: ШІ-12
*/
#include <iostream>

using namespace std;

int main()
{
    long long a[8],maxs=-9999,mins=9999999999999999;
    bool Flip=false;
    for(int i=0;i<8;i++)
    {
        cin>>a[i];
    }
    for(int i=0;i<4;i++)
    {
        if(a[i+4]>a[i]){cout<<"ERROR"<<endl;return 0;}
    }
    for(int i=0;i<4;i++)
    {
        a[i]=a[i]-a[i+4];
        for(int j=0;j<4;j++)
        {
            if(a[j]>maxs)maxs=a[j];
            if(a[j]<mins)mins=a[j];
        }
        if(maxs>=mins*2){cout<<"NO";return 0;}
    }
    cout<<"YES";
    return 0;
}