#include <iostream>
using namespace std;

int main()
{
    long long n, sum=0;
    cin >> n;
    long long a[n];
    
     for (int i=0; i < n; i++)
     {
        cin >> a[i];
        sum+=a[i];
     }
sum=sum-n;
cout << sum;
return 0;
}


