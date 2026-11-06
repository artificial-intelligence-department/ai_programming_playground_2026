/*Алготестер задача 3 варіант 1
Максімко Павло - СШІ-13*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n;
    cin >> n;
    if(cin.fail() || n > 1000 || n < 1)
    {
        cout << "Кількість рядків повинна бути цілим числом від 1 до 1000!" << endl;
        return 1;
    }
    cin.ignore(100000, '\n');
    string s[n];
    for(int i = 0; i < n; i++)
    {
        getline(cin, s[i]);
    }
    bool destroyed = 0;
    int k = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < s[i].size(); j++)
        {
            if(s[i][j] == '#' && destroyed == 0)
            {
                destroyed = 1;
                k++;
            }
            else if(s[i][j] != '#')
            {
                destroyed = 0;
            }
        }
    }

    cout << k << endl;
    return 0;
}