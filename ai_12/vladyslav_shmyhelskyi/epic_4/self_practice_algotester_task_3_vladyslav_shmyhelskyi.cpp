#include <iostream>
using namespace std;

int main()
{

    int n;
    cin >> n;
    
    int difference = 500 - n;
    int cnt = 0;
    int rest = 0;
    if (n == 500)
    {
        cout << "0";
        return 0;
    }
    if (difference / 200 > 0)
    {
        cnt += difference / 200;
        rest = difference % 200;
    }else 
    {
        rest = difference;
    }
    if ((rest / 100) > 0)
    {
        cnt += rest / 100;
        rest = rest % 100;
    }
    if ((rest /50 ) > 0 ){
        cnt += rest/50;
        rest = rest % 50;
    }
    if ((rest/20) > 0)
    {
        cnt += rest/20;
        rest = rest%20;

    }
    if ( (rest/10) > 0)
    {
        cnt += rest/10;
        rest = rest%10;
    }
    if ( (rest/5) > 0)
    {
        cnt += rest/5;
        rest = rest%5;
    }
    if ( (rest/2) > 0)
    {
        cnt += rest/2;
        rest = rest%2;
    }
    if ( (rest/1) > 0)
    {
        cnt += rest/1;
        rest = rest%1;
    }

    cout << cnt;



}