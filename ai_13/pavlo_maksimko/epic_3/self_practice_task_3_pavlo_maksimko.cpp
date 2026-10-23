/*Задача 1172 - Непарний масив
Максімко Павло - СШІ-13*/

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int n, even = 0, odd = 0;
    cin >> n;
    int a[n];
    int odd_num[n];
    int even_num[n];

    int even_i = 0;
    int odd_i = 0;

    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        if(a[i] % 2 == 0) 
        {
            even_num[even_i] = a[i];
            even_i++;
            even++;
        }
        else 
        {
            odd_num[odd_i] = a[i]; 
            odd_i++;
            odd++;
        }
    }

    if(abs(even - odd) > 1) 
    {
        cout << -1 << endl;
        return 0;
    }
    else
    {
        if(even > odd)
        {
            for(int i = 0; i < even_i; i++)
            {
                cout << even_num[i] << " ";
                if(i < odd_i) cout << odd_num[i] << " ";
            }
        }
        else
        {
            for(int i = 0; i < odd_i; i++)
            {
                cout << odd_num[i] << " ";
                if(i < even_i) cout << even_num[i] << " ";
            }
        }
    }

    return 0;
}




