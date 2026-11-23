//Марічка вмикає лампи
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    long long m, n;
    cin >> m >> n;

    double total = (double)(m + 1) / (m - n + 1);

    cout << fixed << setprecision(10) << total;

    return 0;
}