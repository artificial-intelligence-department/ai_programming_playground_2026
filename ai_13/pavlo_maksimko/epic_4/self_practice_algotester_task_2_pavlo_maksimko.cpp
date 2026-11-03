/*Задача 1851 - Цікавий масив
Максімко Павло - СШІ-13*/

#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int *a = new int[n];
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        cin >> *(a + i);
        sum += *(a + i);
    }

    int sum_k = 0;
    for(int i = 0; i < n; i++)
    {
        sum_k += *(a + i);
        if(sum_k == sum - sum_k)
        {
            cout << "TAK" << endl;
            delete[] a;
            a = nullptr;
            return 0;
        }
    }   
    cout << "NI" << endl;
    delete[] a;
    a = nullptr;
    return 0;
}
