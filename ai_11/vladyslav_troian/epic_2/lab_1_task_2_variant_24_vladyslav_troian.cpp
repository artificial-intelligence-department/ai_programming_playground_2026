#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    int m = 0;

    cin >> n;
    cin >> m;

    //Змінні якими повертаю задані значення для n і m
    int fn = n;
    int fm = m;

    int a = (n++*m); //спершу множить значення потім додає 1 до n
    cout << a << endl;
    n = fn;

    bool b = (n++ < m); //перевіряє нерівність потім додає 1 до n
    cout << b << endl;
    n = fn;

    bool c = (m-- > m); //замість m-- ставить початкове значення m, а від іншого віднімає 1
    cout << c << endl;
    m = fm;
    return 0;
}