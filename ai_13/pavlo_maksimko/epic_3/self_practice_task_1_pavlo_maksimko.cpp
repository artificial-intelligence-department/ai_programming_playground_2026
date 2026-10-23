/*Задача 0182 - Зуби
Максімко Павло - СШІ-13*/

#include <iostream>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    int a[n], count = 1, count_max = 1;

    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        if(i != 0 && a[i] >= k && a[i - 1] >= k)
        {
            count++;
        }
        else if(i != 0 && a[i] < k)
        {
            count = 1;
        }
        if(count > count_max) count_max = count;
    }

    cout << count_max << endl;
    return 0;
}