/*
    Задача: Цікавий масив
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    int* a = new int[n];
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        total += a[i];
    }
    int left = 0;
    bool ok = false;
    for (int k = 1; k < n; k++)
    {
        left += a[k - 1];
        if (left == total - left)
        {
            ok = true;
        }
    }
    if (ok)
    {
        cout << "TAK" << endl;
    }
    else 
    {
        cout << "NI" << endl;
    }
    delete[] a;
    return 0;
}