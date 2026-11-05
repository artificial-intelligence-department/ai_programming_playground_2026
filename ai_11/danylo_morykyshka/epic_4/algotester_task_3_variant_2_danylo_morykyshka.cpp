#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int m;
    cin >> m;
    int b[m];
    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
    }
    int countOfPovt = 0;
    int countOfUni = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if(a[i] == b[j]){
                countOfPovt++;
            }
        }
    }
    cout << countOfPovt << endl;
    cout << n + m - countOfPovt << endl;
    
}