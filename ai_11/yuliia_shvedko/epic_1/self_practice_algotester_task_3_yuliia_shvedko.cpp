/*"Марічка і печиво"
Автор: Шведько Юлія
Група: ШІ-11*/

#include <iostream>
using namespace std;

int main()
{
    long long n;
    long long m = 0;
    cin >> n;
    for(long long i = 0; i < n; i++)
    {
        long long a;
        cin >> a;

        if(a > 0)
        {
            m += (a - 1);
        }
    }
    cout << m << endl;
    return 0;
}