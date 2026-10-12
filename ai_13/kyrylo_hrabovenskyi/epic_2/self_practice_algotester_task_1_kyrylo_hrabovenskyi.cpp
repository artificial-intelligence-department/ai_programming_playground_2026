/*
Епік 1. self practice: Algotester, задача "A плюс B"
Грабовенський Кирило
СШІ-13
*/
#include <iostream>
using namespace std;

int main()
{
    int a;
    int b;
    cin >> a;
    cin >> b;
    if (a < 0 || b < 0)
    {
        return 1;
    }
    if (a > 100 || b > 100)
    {
        return 1;
    }
    cout << a + b;
    return 0;
}