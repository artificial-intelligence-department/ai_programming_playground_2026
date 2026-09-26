#include <iostream>

using namespace std;

int main() 
{
    int a;
    int b;

    cin >> a;
    if (a < 0 || a > 100)
    {
        cout << "Число має бути в діапазоні від 0 до 100";
        return 1;
    }
    cin >> b;
    if (b < 0 || b >100)
    {
        cout << "Число має бути в діапазоні від 0 до 100";
        return 1;
    }

    cout << a + b << endl;

    return 0;
}