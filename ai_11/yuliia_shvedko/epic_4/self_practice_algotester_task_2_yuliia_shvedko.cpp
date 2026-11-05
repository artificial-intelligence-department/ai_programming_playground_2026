//Портрети

#include <iostream>
using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    char **r = new char*[n];
    for(int i = 0; i < n; i++)
    r[i] = new char[m];
    int a = 0;
    int b = 0;
    for(int i = 0; i < n; i++)
    {
        a = 0;
        for(int j = 0; j < m; j++)
        {
            cin >> r[i][j];
            if(r[i][j] == '*')
            a++;
        }
        if(a > 0)
        {
            b += (a + k - 1)/k;
        }
    }
    cout << b << endl;

    for(int i = 0; i < n; i++)
    delete[] r[i];
    delete[] r;

    return 0;
}