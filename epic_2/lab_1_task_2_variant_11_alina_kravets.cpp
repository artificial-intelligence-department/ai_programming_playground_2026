#include <iostream>

using namespace std;

int main()
{
    double n = 0.0;
    double m = 0.0;
    double a = 0.0;
    bool b = false;
    bool c = false;

    cout << "Введіть n: ";
    cin >> n;
    cout << "Введіть m: ";
    cin >> m;

    a = n++ * m;
    b = n++ < m;
    c = m-- > m;

    cout << "1) n++*m = " << a << endl;
    cout << "2) n++<m = " << b << endl;
    cout << "3) m-- >m = " << c << endl;
}
