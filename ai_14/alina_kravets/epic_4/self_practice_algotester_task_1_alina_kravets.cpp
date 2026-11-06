/*Цікаве листування
ШІ-14
Кравець Аліна*/
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int n = 0;
    string s;

    cin >> n;
    cin >> s;

    int k = sqrt(n);

    char message[k][k];

    int index = 0;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            message[i][j] = s[index];
            index++;
        }
    }

    for (int i = 0; i < 2*k - 1; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int col = i - j;
            if (col >= 0 && col < k)
            {
                cout << message[j][col];
            }
        }
    }

    return 0;
}
