//Розваги з матрицею

#include <iostream>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    long long **r = new long long*[n];
    for(int i = 0; i < n; i++)
    r[i] = new long long[m];

    bool **q = new bool*[n];
    for(int i = 0; i < n; i++)
    q[i] = new bool[m];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            q[i][j] = false;
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> r[i][j];
        }
    }

    for(int j = 0; j < m; j++)
    {
        long long max = r[0][j];
        for(int i = 0; i < n; i++)
        {
            if(r[i][j] > max)
            {
                max = r[i][j];
            }
        }
        for(int i = 0; i < n; i++)
        {
            if(r[i][j] == max)
            {
                q[i][j] = true;
            }
        }
    }
    
    bool w;
    for(int i = 0; i < n; i++)
    {
        w = true;
        for(int j = 0; j < m; j++)
        {
            if(!q[i][j])
            {
                w = false;
            }
        }
        if(w)
        cout << i + 1 << endl;
        if(w) break;
    }
    if(!w)
    {
        cout << "-1" << endl;
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            q[i][j] = false;
        }
    }

    for(int i = 0; i < n; i++)
    {
        long long min = r[i][0];
        for(int j = 0; j < m; j++)
        {
            if(r[i][j] < min)
            {
                min = r[i][j];
            }
        }
        for(int j = 0; j < m; j++)
        {
            if(r[i][j] == min)
            {
                q[i][j] = true;
            }
        }
    }
    
    for(int j = 0; j < m; j++)
    {
        w = true;
        for(int i = 0; i < n; i++)
        {
            if(!q[i][j])
            {
                w = false;
            }
        }
        if(w)
        cout << j + 1 << endl;
        if(w) break;
    }
    if(!w)
    {
        cout << "-1" << endl;
    }

    for(int i = 0; i < n; i++)
    delete[] r[i];
    delete[] r;
    for(int i = 0; i < n; i++)
    delete[] q[i];
    delete[] q;

    return 0;
}