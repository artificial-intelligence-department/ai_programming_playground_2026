#include <iostream>
int main()
{
    using namespace std;
    // Введення змінних m та n
    double m, n;
    cout << "Enter m:";
    cin >> m;
    cout << "Enter n:";
    cin >> n;
    // example 1
    double m1 = m;
    double n1 = n;
    double res1 = m + (--n1); // обчислення виразу 1
    cout << "result 1:" << res1 << endl;

    // example 2
    bool res2 = ++m < ++n; // перевірка нерівності 2
    if (res2 == true)
    {
        cout << "result 2: true" << endl;
    }
    else
    {
        cout << "result 2: false" << endl;
    }

    // example 3
    bool res3 = --n < --m; // перевірка нерівності 3
    if (res3 == true)
    {
        cout << "result 3: true" << endl;
    }
    else
    {
        cout << "result 3: false" << endl;
    }
}