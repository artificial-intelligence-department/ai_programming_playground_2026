//Лотерея

#include <iostream>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int **r = new int*[n];
    for(int i = 0; i < n; i++)
    r[i] = new int[m];
    int *s = new int[m];

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> r[i][j];
        }
    }

    for(int j = 0; j < m; j++)
    {
        int max = r[0][j];
        for(int i = 0; i < n; i++)
        {
            if(r[i][j] > max)
            {
                max = r[i][j];
            }
        }
        s[j] = max;
    }

    for(int i = 0; i < n; i++)
    delete[] r[i];
    delete[] r;
    
    int min = s[0];
    for(int i = 0; i < m; i++)
    {
        if(s[i] < min)
        min = s[i];
    }

    cout << min << endl;

    delete[] s;

    return 0;
}