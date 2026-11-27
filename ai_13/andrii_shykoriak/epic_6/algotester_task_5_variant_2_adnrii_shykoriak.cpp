#include <iostream>
#include <string>
using namespace std;

int main(){

    int n,m;
    cin >> n >> m;
    int len = n*m;
    string s[n];
    int index = 1;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    for (int i = n-2; i >= 0; i--)
    {
        for (int j = 0; j < m; j++)
        {
            int r = i;
            while (r+1 < n && s[r][j] == 'S' && s[r+1][j] == 'O'){
                s[r+1][j] = 'S';
                s[r][j] = 'O';
                r++;
            }
        }
        
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << s[i] << endl;
    }
    
    return 0;
}