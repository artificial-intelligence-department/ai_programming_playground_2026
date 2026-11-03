/*Симетрична матриця - Задача 2501
Максімко Павло - СШІ-13*/

#include <iostream>
#include <string>

using namespace std;

bool symethry(string *M, int n);

int main()
{
    int n;
    cin >> n;

    string *M = new string[n];

    for(int i = 0; i < n; i++)
    {
        cin >> M[i];
    }

    if(symethry(M, n)) cout << "Yes" << endl;
    else cout << "No" << endl;

    delete[] M;
    M = nullptr;

    return 0;
}

bool symethry(string *M, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(M[i][j] != M[j][i])
            {
                return false;
            }
        }
    }
    return true;
}