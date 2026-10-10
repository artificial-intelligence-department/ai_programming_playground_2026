// Lab 1, task 2, Дрогомирецька Ольга, варіант 1
#include <iostream>
using namespace std;
/*
1) n+++ m
2) m-- > n
3) n-- > m
*/
int main()
{
    int n, m;
    cout << "Введіть значення n:" << endl;
    cin >> n;

    cout << "Введіть значення m:" << endl;
    cin >> m;

    int result1 = n++ + m;
    cout << result1 << endl;

    int result2 = m-- > n;
    cout << result2 << endl;

    int result3 = n-- > m;
    cout << result3 << endl;

    return 0;
}
