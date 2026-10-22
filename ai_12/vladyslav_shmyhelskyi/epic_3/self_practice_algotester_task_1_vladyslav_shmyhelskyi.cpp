#include <iostream>
using namespace std;

int main()
{

    int n, m;
    cin >> n;
    cin >> m;
    if (n < 1 || n > 100)
        return 0;

    if (m < 1 || m > 100)
        return 0;
    int matrix = (n * m) % 2;
    if (matrix == 0)
    {
        cout << "Dragon";
    }
    else
    {
        cout << "Imp";
    }
}