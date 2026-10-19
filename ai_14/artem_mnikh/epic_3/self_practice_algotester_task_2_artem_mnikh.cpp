/*ЛіБрін-ніркімін 1032*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n, k;
    string x;

    int sum = 0;
    cin >> n >> k >> x;
    for (char num : x)
    {
        sum += (num - '0');
    }
    int result = sum % (n - 1);
    if (result == 0)
        cout << n - 1;
    else
        cout << result;
}
