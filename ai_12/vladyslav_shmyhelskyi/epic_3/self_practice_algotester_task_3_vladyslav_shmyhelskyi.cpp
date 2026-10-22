#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double n, k;
    cin >> n;
    cin >> k;
  if (n == 0 || k == 0)
    {
        cout << fixed << setprecision(6) << 0.0 << endl;
    }
    else
    {
        double chance = 1.0 / (n * k);
        cout << fixed << setprecision(6) << chance << endl;
    }
    return 0;
}