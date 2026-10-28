#include <iostream>
using namespace std;

const int N = 100;
int a[N];
int n;
int k;

int main()
{
    cout << "Enter amount of numbers: " << endl;
    cin >> n;
    while (cin.fail() || n > 98 || n < 1)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Mistake! Enter amount of numbers again: " << endl;
        cin >> n;
    }
    cout << "Enter the numbers: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "You only can write the numbers. Enter the numbers again: " << endl;
            cin >> a[i];
        }
    }
    cout << "Choose the number to start from it" << endl;
    cin >> k;
    while (cin.fail() || k > n || k < 1)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "You only can write the number, that is not more than " << n << ". Choose the number again: " << endl;
        cin >> k;
    }
    for (int i = k - 1; i < n; i++)
    {
        cout << a[i] << " ";
    }
    for (int i = 0; i < k - 1; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "Enter two numbers to add them to start and to end: " << endl;
    for (int i = n; i > 0; i--)
    {
        a[i] = a[i - 1];
    }
    cin >> a[0] >> a[n + 1];
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Mistake! Enter two numbers again: " << endl;
        cin >> a[0] >> a[n + 1];
    }

    n += 2;
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "Delete even numbers: " << endl;
    for (int i = 0; i < n; i++)
    {
        if (a[i] % 2 == 0)
        {
            for (int j = i; j < n - 1; j++)
            {
                a[j] = a[j + 1];
            }
            n--;
            i--;
        }
    }
    if (n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            cout << a[i] << " ";
        }
        cout << endl;

        cout << "Choose the number to start from it" << endl;
        cin >> k;
        while (cin.fail() || k > n || k < 1)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "You only can write the number, that is not more than " << n << ". Choose the number again: " << endl;
            cin >> k;
        }
        for (int i = k - 1; i < n; i++)
        {
            cout << a[i] << " ";
        }
        for (int i = 0; i < k - 1; i++)
        {
            cout << a[i] << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "The array is empty!" << endl;
    }

    return 0;
}