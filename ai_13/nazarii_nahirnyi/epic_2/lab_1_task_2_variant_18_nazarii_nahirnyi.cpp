/*
Lab 1 task 2, Нагірний Назарій, ШІ-13, Варіант № 18
*/
#include <iostream>
using namespace std;

/*
1) n++ * m
2) n++ < m
3) m-- > m
*/

int main()
{
    int n0, m0;
    cout << "n: "; cin >> n0;
    cout << "m: "; cin >> m0;

    int n = n0, m = m0;
    int r1 = n++ * m;
    cout << "1) n++ * m = " << r1 << " (n=" << n << ")" << endl;

    n = n0; m = m0;
    bool r2 = n++ < m;
    cout << "2) n++ < m = " << r2 << " (n=" << n << ")" << endl;

    n = n0; m = m0;
    bool r3 = m-- > m;
    cout << "3) m-- > m = " << r3 << " (m=" << m << ")" << endl;

    return 0;
}