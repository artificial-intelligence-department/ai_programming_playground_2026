//Степан на карантині
#include <iostream>

using namespace std;

int main()
{
    int n,k;
    cin >> n >> k;
    int count = 0;

    int c[n];

    for(int i = 0; i < n;i++)
    {
        cin >> c[i];
    }

    for(int i = 0; i < n;i++)
    {
        if(c[i] > k)
        {
            count++;
        }
    }

    cout << count;


}