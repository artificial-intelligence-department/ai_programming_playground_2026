/*Задача 0791 - Дозволена динаміка
Максімко Павло - СШІ-13*/

#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

int main()
{
    int n;
    cin >> n;
    pair<long long, long long> *b = new pair<long long, long long>[n];
    for(int i = 0; i < n; i++)
    {
        long long x;
        cin >> x;
        b[i].first = x - i;
        b[i].second = x + i;
    }
    sort(b, b + n);
    for(int i = 0; i < n - 1; i++)
    {
        if(b[i + 1].second < b[i].second)
        {
            cout << "NO" << endl;
            delete[] b;
            b = nullptr;
            return 0;
        }
    }
    cout << "YES" << endl;
    delete[] b;
    b = nullptr;
    return 0;
}