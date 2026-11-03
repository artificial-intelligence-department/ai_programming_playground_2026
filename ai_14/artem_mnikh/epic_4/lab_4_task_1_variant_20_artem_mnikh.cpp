#include <iostream>

using namespace std;

int main()
{
    int n;
    cout << "Введіть розмір масиву: ";
    while (!(cin >> n) || n <= 0 || n >= 100)
    {
        cout << "Введіть число з проміжку (0, 100)" << '\n';
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');

    int* m = new int[n];
    for (int i = 0; i < n; ++i)
    {
        cout << "Залишилось ввести " << n - i << " значень:" << '\n';
        while (!(cin >> m[i]))
        {
            cout << "Введіть число" << '\n';
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');
    }
    cout << "Введіть k: ";
    int k;
    while (!(cin >> k) || k < 0 || k >= n)
    {
        cout << "Введіть індекс, який не виходить за межі масиву" << '\n';
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');

    cout << "Виведення від k до k - 1:      ";
    for (int i = 0; i < n; ++i)
    {
        int current_index = (k + i) % n;
        cout << m[current_index] << " ";
    }
    cout << endl;
    int resize_value = (n - 1) / 5 + 1;
    int* temp = new int[n + resize_value];
    int j = -1;
    for (int i = 0; i < n; ++i)
    {
        ++j;
        if (i % 5 == 0)
        {
            temp[j] = m[i];
            temp[j + 1] = 0;
            ++j;
        }
        else
        {
            temp[j] = m[i];
        }
    }
    delete[] m;
    m = temp;
    temp = nullptr;
    k += (k == 0 ? 0 : (k - 1) / 5 + 1);
    cout << "Виведення масиву з 0:          ";
    for (int i = 0; i < n + resize_value; ++i)
    {
        int current_index = (k - i + n + resize_value) % (n + resize_value);
        cout << m[current_index] << " ";
    }
    delete[] m;
    m = nullptr;
}