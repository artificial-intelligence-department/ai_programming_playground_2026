//Депутатські гроші
#include <iostream>

using namespace std;

int main()
{
    int currency[] = {1, 2, 5, 10, 20, 50, 100, 200, 500};

    int count = 0;

    int n;
    cin >> n;

    for(int i = 8;i >= 0;i--)
    {
        count += n / currency[i];
        n %= currency[i];
    }

    cout << count;
    
}