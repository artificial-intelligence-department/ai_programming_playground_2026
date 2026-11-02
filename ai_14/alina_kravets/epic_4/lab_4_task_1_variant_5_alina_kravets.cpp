/*Лабораторна №4 варіант №5
ШІ-14
Кравець Аліна*/
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(nullptr));
    int n = 10;
    int a[n] = {0};
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
    }
    cout << "Масив на початку: {";
    for (int i = 0; i < n; i++)
    {
        cout << a[i];
        if (i != n-1) cout << ", ";
    }
    cout << "}" << endl;

    int count1 = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i]%7 != 0) count1++;
    }
    int copy[count1] = {0};
    int j = 0;
    for (int i = 0; i < n; i++)
    { 
        if (a[i]%7 != 0)
        {
            copy[j] = a[i];
            j++;
        }
    }
    
    int count2 = 0;
    for (int i = 0; i < count1; i++)
    {
        if (copy[i]%2 == 1) count2++;
    }
    int size = count1+count2;
    int final[size] = {0};
    j = 0;
    for (int i = 0; i < count1; i++)
    {
        final[j] = copy[i];
        if (copy[i]%2 == 1) j +=2;
        else j++;
    }

    cout << "Кінцевий масив: {";
    for (int i = 0; i < size; i++)
    {
        cout << final[i];
        if (i != size-1) cout << ", ";
    }
    cout << "}" << endl;

    return 0;
}
