#include <iostream>
#include <string>
using namespace std;
int main()
{
    int indexDay;
    string d;
    cin >> d;
    if (d == "Monday")
    {
        indexDay = 0;
    }
    else if (d == "Tuesday")
    {
        indexDay = 1;
    }
    else if (d == "Wednesday")
    {
        indexDay = 2;
    }

    else if (d == "Thursday")
    {
        indexDay = 3;
    }
    else if (d == "Friday")
    {
        indexDay = 4;
    }
    else if (d == "Saturday")
    {
        indexDay = 5;
    }
    else if (d == "Sunday")
    {
        indexDay = 6;
    }

    int d1, d2, d3, d4, d5, d6, d7;
    long long n;
    cin >> n;
    long long days[7];
    for (int i = 0; i < 7; i++)
    {
        days[i] = 0;
    }

    int rest = n % 7;
    for (int i = 0; i < rest; i++)
    {

        int currentday = (indexDay + i) % 7;

        days[currentday]++;
    }

    for (int i = 0; i < 7; i++)
    {

        days[i] += (n / 7);
    }

    for (int i = 0; i < 7; i++)
    {
        cout << days[i] << " ";
    }
    return 0;
}