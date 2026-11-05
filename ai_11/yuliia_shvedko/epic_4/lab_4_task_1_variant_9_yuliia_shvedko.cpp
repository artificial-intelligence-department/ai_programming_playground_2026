/*Лабораторна 4
Варіант: 9*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(time(nullptr));
    const int N = 100;
    cout << "Ввeдіть кількість елементів масиву: ";
    int n;
    cin >> n;
    if(cin.fail() || n < 1)
    {
        cout << "Кількість елементів масиву має бути натуральним числом!" << endl;
        return 1;
    }
    cout << "Початковий масив:" << endl;
    int m[N];
    for(int i = 0; i < n; i++)
    {
        m[i] = rand() % 100;
        cout << m[i] << " ";
    }
    cout << endl;
    cout << "Введіть значення елемента який хочете знищити: ";
    int e;
    cin >> e;

    int q = -1;
    for(int i = 0; i < n; i++)
    {
        if(m[i] == e)
        {
            q = i;
            break;
        }
    }
    if(q == -1)
    {
        cout << "Елемента з таким значенням немає в масиві!" << endl;
        return 1;
    }

    for(int i = q; i < n; i++)
    m[i] = m[i + 1];

    cout << "На скільки елементів зсунути масив? ";
    int k;
    cin >> k;
    if(cin.fail() || n < 1)
    {
        cout << "Значення має бути цілим числом!" << endl;
        return 1;
    }
    k = k % (n - 1);
    cout << "Отриманий масив: " << endl;
    int mm[N];
    for(int i = 0; i < n - 1; i++)
    {
        if((i - k) < 0)
        mm[i] = m[i - k + n - 1];
        else
        mm[i] = m[i - k];
        cout << mm[i] << " ";
    }
    cout << endl;
    return 0;
}